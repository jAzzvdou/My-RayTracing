/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:29:32 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 13:03:00 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double	bhaskara(t_object o, t_ray r)
{
	double		abc[3];
	t_vector	to_ray;

	to_ray = sub_tuple(r.origin, o.origin);
	abc[0] = dot(r.direction, r.direction);
	abc[1] = 2 * dot(r.direction, to_ray);
	abc[2] = dot(to_ray, to_ray) - 1;
	return ((abc[1] * abc[1]) - (4 * abc[0] * abc[2]));
}

t_intersection	intersection(t_object o, double t)
{
	t_intersection	inter;

	inter.object = o;
	inter.t = t;
	inter.next = NULL;
	return (inter);
}

int	count_intersection(t_intersection *list)
{
	int				count;
	t_intersection	*tmp;

	count = 0;
	tmp = list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	add_intersection(t_intersection **list, t_intersection inter)
{
	t_intersection	*new;
	t_intersection	*tmp;
	t_intersection	*prev;

	new = memcard(NULL, DEFAULT, MALLOC, sizeof(t_intersection));
	*new = inter;
	prev = NULL;
	tmp = *list;
	while (tmp && tmp->t < inter.t)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
	{
		prev->next = new;
		new->next = tmp;
		return ;
	}
	new->next = *list;
	*list = new;
}
