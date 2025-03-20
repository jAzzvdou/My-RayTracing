/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:08:00 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/19 23:27:28 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_world	world(void)
{
	t_world	w;

	my_bzero(&w, sizeof(t_world));
	//w.amb.has_cam = 0;
	return (w);
}

void	add_light(t_light **l1, t_light l2)
{
	t_light	*new;
	t_light	*tmp;

	new = memcard(NULL, DEFAULT, MALLOC, sizeof(t_light));
	*new = l2;
	tmp = *l1;
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*l1 = new;
}

void	add_object(t_object **obj1, t_object obj2)
{
	t_object	*new;
	t_object	*tmp;

	new = memcard(NULL, DEFAULT, MALLOC, sizeof(t_object));
	*new = obj2;
	tmp = *obj1;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if(tmp)
		tmp->next = new;
	else
		*obj1 = new;
}

t_intersection	*intersect_world(t_world w, t_ray r)
{
	t_object	*tmp;
	t_intersection	*list;

	list = NULL;
	tmp = w.object;
	while(tmp)
	{
		intersect(&list, *tmp, r);
		tmp = tmp->next;
	}
	return (list);
}

t_comps	prepare_computations(t_intersection inter, t_ray ray, t_intersection *xs)
{
	t_comps	comps;

	my_bzero(&comps, sizeof(t_comps));
	comps.t = inter.t;
	comps.object = inter.object;
	comps.inside = false;
	comps.point = position(ray, comps.t);
	comps.eyev = inverse_tuple(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.in_shadow = false;
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = inverse_tuple(comps.normalv);
	}
	comps.over_point = add_tuple(comps.point, mult_tuple(comps.normalv, EPSILON));
	comps.under_point = sub_tuple(comps.point, mult_tuple(comps.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.normalv);
	calculate_index(&comps, xs);
	return (comps);
}
