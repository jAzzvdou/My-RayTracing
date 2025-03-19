/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:33:57 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/18 22:15:51 by jbergfel         ###   ########.fr       */
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
	t_color	n_color;
	t_point	p;
	t_light	n_light;
	double	bright;
	char	**line_split;

	printf("----------Light PARSE----------\n");
	(void) w;
	line_split = my_split(line, ' ');
	if (!valid_line_count(line_split, 4) || !get_coords(line_split[1], &p) || !set_bright(line_split[2], &bright) || !get_color(line_split[3], &n_color))
	{
		printf("bright parse ko\n");
		//free split
		return (0);
	}
	//free split
	n_light = point_light(p, mult_color(n_color, bright));
	add_light(&w->light, n_light);
	printf("Intensity -> %f\n", bright);
	printf("bright parse ok\n\n");
	return (1);
}
