/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:08:09 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/18 00:52:44 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	if (!texture.img)
	{
		err(NULL, "Error\nTexture not found", NULL);
		exit(1);
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.linelen, &texture.endian);
	return (texture);
}

t_pattern	new_pattern(t_pattern_type type, t_color a, t_color b, void *mlx)
{
	t_pattern	p;

	my_bzero(&p, sizeof(t_pattern));
	p.has_pattern = true;
	p.a = a;
	p.b = b;
	p.inversed = identity();
	p.transformed = identity();
	p.texture = load_texture(mlx, "10Patterns/Textures/camuflagem.xpm");
	if (type == STRIPE)
		p.type = STRIPE;
	else if (type == GRADIENT)
		p.type = GRADIENT;
	else if (type == RING)
		p.type = RING;
	else if (type == CHECKER)
		p.type = CHECKER;
	else if (type == TEXTURE)
		p.type = TEXTURE;
	else
		p.type = NO_TYPE;
	return (p);
}

t_color	stripe_at(t_pattern p, t_point pt)
{
	if ((int)floor(pt.x) % 2 == 0)
		return (p.a);
	return (p.b);
}

t_color	gradient_at(t_pattern p, t_point pt)
{
	double	fraction;
	t_color	distance;

	distance = sub_color(p.b, p.a);
	fraction = fmod(fabs(pt.x), 1);
	if (fmod(fabs(pt.x), 2) >= 1)
		fraction = 1 - fmod(fabs(pt.x), 1);
	return (add_color(mult_color(distance, fraction), p.a));
}

int	near_zero(double nb)
{
	return (nb < EPSILON && nb > -EPSILON);
}

t_color	ring_at(t_pattern p, t_point pt)
{
	double	discriminant;

	discriminant = floor(sqrt(pow(pt.x, 2) + pow(pt.z, 2)));
	if (near_zero(fmod(discriminant, 2)))
		return (p.a);
	return (p.b);
}

t_color	checker_at(t_pattern p, t_point pt)
{
	int	mod;
	int	sum;

	mod = 1;
	sum = (int)(pt.x + pt.y + pt.z);
	if (sum % 2 == 0)
		mod = 0;
	if (pt.x < 0)
		mod = !mod;
	if (pt.z < 0)
		mod = !mod;
	if (mod)
		return (p.a);
	return (p.b);
}

t_color	texture_color(t_texture tex, t_uv uv)
{
	int x = floor(uv.u * (tex.width - 1));
	int y = floor(uv.v * (tex.height - 1));

	int pixel = (y * tex.linelen) + (x * (tex.bpp / 8));
	unsigned char *color = (unsigned char *)(tex.addr + pixel);

	return ((t_color){color[2] / 255.0, color[1] / 255.0, color[0] / 255.0});
}

t_color	sphere_texture(t_pattern p, t_point pt)
{
	t_uv	uv;
	double	phi;
	double	theta;

	theta = atan2(pt.x, pt.z);
	phi = acos(pt.y);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = 1 - (phi / M_PI);
	return (texture_color(p.texture, uv));
}

t_color	plane_texture(t_pattern p, t_point pt)
{
	t_uv	uv;

	uv.u = fmod(pt.x, 1);
	uv.v = fmod(pt.z, 1);
	return (texture_color(p.texture, uv));
}

t_color	cylinder_texture(t_pattern p, t_point pt)
{
	t_uv	uv;
	double	theta;

	theta = atan2(pt.x, pt.z);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = fmod(pt.y, 1);
	return (texture_color(p.texture, uv));
}

t_color	cone_texture(t_pattern p, t_point pt)
{
	t_uv	uv;
	double	theta;
	double	radius;

	radius = pow(pt.x, 2) + pow(pt.z, 2);
	theta = atan2(pt.x, pt.z);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = fmod(sqrt(radius), 1);
	return (texture_color(p.texture, uv));
}

t_color	texture_at(t_pattern p, t_object obj, t_point pt)
{
	if (obj.type == SP)
		return (sphere_texture(p, pt));
	if (obj.type == PL)
		return (plane_texture(p, pt));
	if (obj.type == CY)
		return (cylinder_texture(p, pt));
	if (obj.type == CN)
		return (cone_texture(p, pt));
	return (color(0, 0, 0));
}

t_color	pattern_at_object(t_pattern pattern, t_object obj, t_point point)
{
	t_point	obj_point;
	t_point pat_point;

	obj_point = mult_matrix_tuple(obj.inversed, point);
	pat_point = mult_matrix_tuple(pattern.inversed, obj_point);
	if (pattern.type == STRIPE)
		return (stripe_at(pattern, pat_point));
	if (pattern.type == GRADIENT)
		return (gradient_at(pattern, pat_point));
	if (pattern.type == RING)
		return (ring_at(pattern, pat_point));
	if (pattern.type == CHECKER)
		return (checker_at(pattern, pat_point));
	if (pattern.type == TEXTURE)
		return (texture_at(pattern, obj, obj_point));
	return (pattern.a);
}

void	set_pattern_transform(t_pattern *p, t_matrix transform)
{
	p->transformed = transform;
	p->inversed = inverse(transform);
}
