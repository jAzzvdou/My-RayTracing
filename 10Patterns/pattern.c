/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:08:09 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/26 10:19:50 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path,
			&texture.width, &texture.height);
	if (!texture.img)
	{
		err(NULL, "Error\nTexture not found", NULL);
		exit(1);
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp,
			&texture.linelen, &texture.endian);
	return (texture);
}

t_pattern	new_pattern(t_pat_tp tp, t_color *ab, char *ph, void *mlx)
{
	t_pattern	p;

	my_bzero(&p, sizeof(t_pattern));
	p.has_pattern = true;
	p.a = ab[0];
	p.b = ab[1];
	p.inversed = identity();
	p.transformed = identity();
	if (ph)
		p.texture = load_texture(mlx, ph);
	if (tp == STRIPE)
		p.tp = STRIPE;
	else if (tp == GRADIENT)
		p.tp = GRADIENT;
	else if (tp == RING)
		p.tp = RING;
	else if (tp == CHECKER)
		p.tp = CHECKER;
	else if (tp == TEXTURE)
		p.tp = TEXTURE;
	else
		p.tp = NO_TYPE;
	set_pattern_transform(&p, scaling(0.25, 0.25, 0.25));
	return (p);
}

t_color	texture_color(t_texture tex, t_uv uv)
{
	int				x;
	int				y;
	int				pixel;
	unsigned char	*color;

	if (!tex.addr)
		return ((t_color){0, 0, 0});
	uv.u = fmod(fabs(uv.u), 1.0);
	uv.v = fmod(fabs(uv.v), 1.0);
	x = fmax(0, fmin(floor(uv.u * (tex.width - 1)), tex.width - 1));
	y = fmax(0, fmin(floor(uv.v * (tex.height - 1)), tex.height - 1));
	pixel = (y * tex.linelen) + (x * (tex.bpp / 8));
	color = (unsigned char *)(tex.addr + pixel);
	return ((t_color){color[2] / 255.0, color[1] / 255.0, color[0] / 255.0});
}

t_color	pattern_at_object(t_pattern pattern, t_object obj, t_point point)
{
	t_point	obj_point;
	t_point	pat_point;

	obj_point = mult_matrix_tuple(obj.inversed, point);
	pat_point = mult_matrix_tuple(pattern.inversed, obj_point);
	if (pattern.tp == STRIPE)
		return (stripe_at(pattern, pat_point));
	if (pattern.tp == GRADIENT)
		return (gradient_at(pattern, pat_point));
	if (pattern.tp == RING)
		return (ring_at(pattern, pat_point));
	if (pattern.tp == CHECKER)
		return (checker_at(pattern, pat_point));
	if (pattern.tp == TEXTURE)
		return (texture_at(pattern, obj, obj_point));
	return (pattern.a);
}

void	set_pattern_transform(t_pattern *p, t_matrix transform)
{
	p->transformed = transform;
	p->inversed = inverse(transform);
}
