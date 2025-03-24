/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:46:35 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/24 11:54:01 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	plane_parse(t_world *w, char *line)
{
	char		**splited;
	t_point		p;
	t_vector	n;
	t_object	n_pl;

	n_pl = new_object(PL);
	//n_pl.material = material();
	splited = my_split(line, ' ');
	if (!valid_line_count(splited, 9)
		|| !get_coords(splited[1], &p)
		|| !get_dir(splited[2], &n)
		|| !get_color(splited[3], &n_pl.material.color))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! plane_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_pl.normal = n;
	n_pl.origin = p;
	set_transform(&n_pl, rotate_matrix(p, n, n_pl));
	add_object(&w->object, n_pl);
	return (1);
}
