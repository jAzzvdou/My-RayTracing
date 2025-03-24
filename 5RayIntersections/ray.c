/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:07:35 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/18 01:39:40 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_ray	ray(t_point p, t_vector v)
{
	t_ray	r;

	r.origin = p;
	r.direction = v;
	return (r);
}

t_point	position(t_ray r, double t)
{
	return (add_tuple(r.origin, mult_tuple(r.direction, t)));
}

t_intersection	*hit(t_intersection *inter)
{
	t_intersection	*tmp;

	tmp = inter;
	while (tmp && tmp->t < 0)
		tmp = tmp->next;
	return (tmp);
}

void	set_transform(t_object *o, t_matrix m)
{
	o->transformed = m;
	o->inversed = inverse(m);
	o->transposed = transpose(o->inversed);
}
