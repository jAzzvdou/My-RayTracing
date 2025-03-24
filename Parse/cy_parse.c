/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:54:39 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/24 11:53:52 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	cy_parse(t_world *w, char *line)
{
	char		**splited;
	t_point		p;
	t_vector	n;
	t_object	n_cy;

	n_cy = new_object(CY);
	splited = my_split(line, ' ');
	if (!valid_line_count(splited, 9)
		||!get_coords(splited[1], &p)
		|| !get_dir(splited[2], &n)
		|| !get_double(splited[3], &n_cy.radius)
		|| !get_double(splited[4], &n_cy.maximum)
		|| !get_color(splited[5], &n_cy.material.color))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! cylinder_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_cy.radius /= 2;
	n_cy.maximum /= n_cy.radius;
	n_cy.minimum = 0;
	n_cy.closed = false;
	set_transform(&n_cy, rotate_matrix(p, n, n_cy));
	add_object(&w->object, n_cy);
	return (1);
}
