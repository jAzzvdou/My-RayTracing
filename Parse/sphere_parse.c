/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:26:13 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/22 15:29:15 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	sphere_parse(t_world *w, char *line)
{
	char		**line_spl;
	t_point		p;
	t_object	n_sp;

	n_sp = new_object(SP);
	n_sp.material = material();
	line_spl = my_split(line, ' ');
	if (!get_coords(line_spl[1], &p)
		|| !get_radius(line_spl[2], &n_sp.radius)
		|| !get_color(line_spl[3], &n_sp.material.color) /*|| !get_pattern(line_spl, &n_sp.material, w)*/)
	{
		line_spl = memcard(line_spl, VECTOR, FREE, 0);
		return (err(RED, "Error! sphere_parse ko\n", RESET), 0);
	}
	line_spl = memcard(line_spl, VECTOR, FREE, 0);
	n_sp.radius /= 2;
	set_transform(&n_sp, rotate_matrix(p, point(0, 1, 0), n_sp));
	add_object(&w->object, n_sp);
	return (1);
}
