/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_shading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:07:39 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 13:14:04 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_light	point_light(t_point p, t_color c)
{
	t_light	light;

	light.position = p;
	light.intensity = c;
	light.next = NULL;
	return (light);
}

t_color	clamp_color(t_color c)
{
	c.r = fmin(fmax(c.r, 0), 1);
	c.g = fmin(fmax(c.g, 0), 1);
	c.b = fmin(fmax(c.b, 0), 1);
	return (c);
}

t_color	calc_diff_spec(t_light l, t_comps cm, t_color bc, t_vector *v)
{
	double		d[3];
	t_color		c[2];

	v[0] = normalize(sub_tuple(l.position, cm.point));
	d[0] = dot(v[0], cm.normalv);
	if (d[0] < 0)
	{
		c[0] = color(0, 0, 0);
		c[1] = color(0, 0, 0);
	}
	else
	{
		c[0] = mult_color(bc, cm.object.material.diff * d[0]);
		v[1] = reflect(inverse_tuple(v[0]), cm.normalv);
		d[1] = dot(v[1], cm.eyev);
		if (d[1] <= 0)
			c[1] = color(0, 0, 0);
		else
		{
			d[2] = pow(d[1], cm.object.material.shiny);
			c[1] = mult_color(l.intensity, cm.object.material.spec * d[2]);
		}
	}
	return (add_color(c[0], c[1]));
}

t_color	lighting(t_light l, t_comps comps)
{
	t_color		base_color;
	t_color		ambient;
	t_color		diffuse_specular;
	t_material	m;
	t_vector	v[2];

	m = comps.object.material;
	base_color = m.color;
	if (m.pattern.has_pattern)
		base_color = pattern_at_object(m.pattern, comps.object, comps.point);
	base_color = hadama_color(base_color, l.intensity);
	ambient = hadama_color(base_color, m.amb);
	if (comps.in_shadow)
		return (ambient);
	diffuse_specular = calc_diff_spec(l, comps, base_color, v);
	return (clamp_color(add_color(ambient, diffuse_specular)));
}

t_material	material(void)
{
	t_material	m;

	my_bzero(&m, sizeof(t_material));
	m.color = color(1, 1, 1);
	m.amb = color(1, 1, 1);
	m.diff = 0.9;
	m.spec = 0.9;
	m.shiny = 200.0;
	m.transparency = 0.0;
	m.refractive_index = 1.0;
	return (m);
}
