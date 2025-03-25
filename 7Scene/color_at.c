/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:29:49 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:29:50 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

bool	is_shadowed(t_world w, t_point p, t_light *light)
{
	double		distance;
	t_vector	lightv;
	t_intersection	*inters_list;
	t_intersection	*i;

	lightv = sub_tuple(light->position, p);
	distance = magnitude(lightv);
	inters_list = intersect_world(w, ray(p, normalize(lightv)));
	i = hit(inters_list);
	if (i != NULL && (int)(i->t * 100000) < (int)(distance * 100000))
		return (true);
	return (false);
}

t_color	shade_hit(t_world w, t_comps comps, int remaining)
{
	t_color	reflected;
	t_color	refracted;
	t_color	shaded;
	t_light	*tmp;

	shaded = color(0, 0, 0);
	tmp = w.light;
	while (tmp)
	{
		comps.in_shadow = is_shadowed(w, comps.over_point, tmp);
		shaded = add_color(shaded, lighting(*tmp, comps));
		tmp = tmp->next;
	}
	reflected = reflected_color(w, comps, remaining);
	refracted = refracted_color(w, comps, remaining);
	return (clamp_color(add_color(add_color(shaded, reflected), refracted)));
}

t_color	color_at(t_world w, t_ray r, int remaining)
{
	t_intersection	*h;
	t_comps		comps;

	h = hit(intersect_world(w, r));
	if (!h)
		return (color(0, 0, 0));
	comps = prepare_computations(*h, r, h);
	return (shade_hit(w, comps, remaining));
}
