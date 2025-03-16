/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:46:35 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/16 17:13:56 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	plane_parse(t_world *w, char *line)
{
	t_point	p;
	t_vector	n;
	t_object	n_pl;
	char	**arr;

	printf("----------PLANE PARSE----------\n");

	n_pl = new_object(PL);
	arr = my_split(line, ' ');
	if (!get_coords(arr[1], &p) || !get_dir(arr[2], &n) || !get_color(arr[3], &n_pl.material.color))
	{
		printf("Plane parse ko\n");
		//split free
		return (0);
	}
	//split free
	//set_transform(&n_pl, );
	add_object(&w->object, n_pl);
	printf("Plane parse ok\n");
	return (1);
}
