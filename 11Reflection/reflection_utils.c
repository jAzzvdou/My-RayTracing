/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:32:52 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:33:05 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	is_same_object(t_object object1, t_object object2)
{
	return (object1.id == object2.id);
}

int	float_compare(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}

int	is_same_hit(t_intersection *hit_list, t_intersection hit)
{
	return (float_compare(hit_list->t, hit.t)
		&& is_same_object(hit_list->object, hit.object));
}

t_intersection	intersection2(double t, t_object s)
{
	return ((t_intersection){.t = t, .object = s, .next = NULL});
}

t_object	get_last_object(t_object *object_list)
{
	t_object	*aux;

	aux = object_list;
	while (aux && aux->next)
		aux = aux->next;
	return (*aux);
}
