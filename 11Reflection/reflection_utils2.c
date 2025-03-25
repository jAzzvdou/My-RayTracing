/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:33:56 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:37:40 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

double	get_n1_refract(t_object *containers)
{
	double	refract;

	if (!containers)
		refract = 1.0;
	else
		refract = get_last_object(containers).material.refractive_index;
	return (refract);
}

void	add_object_to_container(t_object **containers, t_object object)
{
	t_object	*aux;
	t_object	*new_object;

	aux = *containers;
	new_object = malloc(sizeof(t_object));
	*new_object = object;
	new_object->next = NULL;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new_object;
	}
	else
		*containers = new_object;
}

void	remove_object_from_container(t_object **containers, t_object object)
{
	t_object	*aux;
	t_object	*prev;

	aux = *containers;
	prev = NULL;
	while (aux)
	{
		if (is_same_object(*aux, object))
		{
			if (prev)
				prev->next = aux->next;
			else
				*containers = aux->next;
			free(aux);
			break ;
		}
		prev = aux;
		aux = aux->next;
	}
}

int	has_object(t_object *containers, t_object obj)
{
	t_object	*aux;

	aux = containers;
	while (aux)
	{
		if (is_same_object(*aux, obj))
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	update_containers(t_object **containers, t_object object)
{
	if (has_object(*containers, object))
		remove_object_from_container(containers, object);
	else
		add_object_to_container(containers, object);
}
