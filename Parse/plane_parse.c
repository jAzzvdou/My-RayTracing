/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:46:35 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/22 16:06:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	plane_parse(t_world *w, char *line)
{
	char		**arr;
	t_point		p;
	t_vector	n;
	t_object	n_pl;

	n_pl = new_object(PL);
	n_pl.material = material();
	arr = my_split(line, ' ');
	if (!get_coords(arr[1], &p)
		|| !get_dir(arr[2], &n)
		|| !get_color(arr[3], &n_pl.material.color))
	{
		arr = memcard(arr, VECTOR, FREE, 0);
		return (err(RED, "Error! plane_parse ko\n", RESET), 0);
	}
	n_pl.normal = n;
	n_pl.origin = p;
	arr = memcard(arr, VECTOR, FREE, 0);
	set_transform(&n_pl, rotate_matrix(p, n, n_pl));
	add_object(&w->object, n_pl);
	return (1);
}
