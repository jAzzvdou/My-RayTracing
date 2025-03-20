/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:54:39 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/20 00:15:40 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	cy_parse(t_world *w, char *line)
{
	char		**arr;
	t_point		p;
	t_vector	n;
	t_object	n_cy;

	n_cy = new_object(CY);
	arr = my_split(line, ' ');
	if (!get_coords(arr[1], &p)
		|| !get_dir(arr[2], &n)
		|| !get_double(arr[3], &n_cy.radius)
		|| !get_double(arr[4], &n_cy.maximum)
		|| !get_color(arr[5], &n_cy.material.color))
	{
		arr = memcard(arr, VECTOR, FREE, 0);
		return (err(RED, "Error! cylinder_parse ko\n", RESET), 0);
	}
	arr = memcard(arr, VECTOR, FREE, 0);
	n_cy.radius /= 2;
	n_cy.maximum /= n_cy.radius;
	n_cy.minimum = 0;
	n_cy.closed = true;
	//set_transform(&n_cy, );
	add_object(&w->object, n_cy);
	return (1);
}
