/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:08:14 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:35:02 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_color	reflected_color(t_world w, t_comps comps, int remaining)
{
	t_ray	reflect_ray;
	t_color	c;

	if (comps.object.material.reflective == 0 || remaining <= 0)
		return (color(0, 0, 0));
	reflect_ray = ray(comps.over_point, comps.reflectv);
	c = color_at(w, reflect_ray, remaining - 1);
	return (clamp_color(mult_color(c, comps.object.material.reflective)));
}

t_color	refracted_color(t_world w, t_comps comps, int depth)
{
	t_ray	refracted_ray;
	double	n_ratio;
	double	cos_i;
	double	cos_t;
	double	sin2_t;

	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.eyev, comps.normalv);
	sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));
	if (comps.object.material.transparency == 0 || depth == 0 || sin2_t > 1)
		return (color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	refracted_ray = ray(comps.under_point,
			sub_tuple(mult_tuple(comps.normalv, (n_ratio * cos_i) - cos_t),
				mult_tuple(comps.eyev, n_ratio)));
	return (clamp_color(mult_color(color_at(w, refracted_ray, depth - 1),
				comps.object.material.transparency)));
}

void	object_clear_list(t_object **object_list)
{
	if (object_list && *object_list)
	{
		object_clear_list(&((*object_list)->next));
		free(*object_list);
		*object_list = NULL;
	}
}

void	calculate_index(t_comps *comps, t_intersection *xs)
{
	t_intersection	*aux_hit;
	t_object		*cnt;

	aux_hit = xs;
	cnt = NULL;
	while (aux_hit)
	{
		if (is_same_hit(aux_hit, intersection2(comps->t, comps->object)))
			comps->n1 = get_n1_refract(cnt);
		update_containers(&cnt, aux_hit->object);
		if (is_same_hit(aux_hit, intersection2(comps->t, comps->object)))
		{
			if (!cnt)
				comps->n2 = 1.0;
			else
				comps->n2 = get_last_object(cnt).material.refractive_index;
			break ;
		}
		aux_hit = aux_hit->next;
	}
	object_clear_list(&cnt);
}
