/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:26:13 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/16 12:09:55 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	sphere_parse(t_world *w, char *line)
{
	t_point		p;
	t_object	n_sp;
	char		**line_spl;

	printf("----------SP PARSE----------\n");
	(void) w;
	n_sp = new_object(SP);
	line_spl = my_split(line, ' ');
	if (!get_coords(line_spl[1], &p) || !get_radius(line_spl[2], &n_sp.radius) || !get_color(line_spl[3], &n_sp.material.color) /*|| !get_pattern(line_spl, &n_sp.material, w)*/)
	{
		printf("Sphere parse ko\n");
		//split free
		return (0);
	}
	//split free
	n_sp.radius /= 2;
	printf("radius r -> %f\n", n_sp.radius);
	//set_transform(&n_sp, );
	add_object(&w->object, n_sp);
	printf("Sphere parse ok\n\n");
	return (1);
}
