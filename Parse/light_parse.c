/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:33:57 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/20 00:10:33 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	set_bright(char *str, double *bright)
{
	if (!get_double(str, bright) || !(*bright >= 0 && *bright <= 1))
		return (printf("set bright wrong\n"), 0);
	return (1);
}

int	light_parse(t_world *w, char *line)
{
	double	bright;
	char	**line_split;
	t_color	n_color;
	t_point	p;
	t_light	n_light;

	(void)w;
	line_split = my_split(line, ' ');
	if (!valid_line_count(line_split, 4)
		|| !get_coords(line_split[1], &p)
		|| !set_bright(line_split[2], &bright)
		|| !get_color(line_split[3], &n_color))
	{
		line_split = memcard(line_split, VECTOR, FREE, 0);
		return (err(RED, "Error! light_parse ko\n", RESET), 0);
	}
	line_split = memcard(line_split, VECTOR, FREE, 0);
	n_light = point_light(p, mult_color(n_color, bright));
	add_light(&w->light, n_light);
	return (1);
}
