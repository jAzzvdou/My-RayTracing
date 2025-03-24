/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:33:57 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/24 11:12:20 by jazevedo         ###   ########.fr       */
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
	char	**splited;
	t_color	n_color;
	t_point	p;

	splited = my_split(line, ' ');
	if (!valid_line_count(splited, 4)
		|| !get_coords(splited[1], &p)
		|| !set_bright(splited[2], &bright)
		|| !get_color(splited[3], &n_color))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! light_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	add_light(&w->light, point_light(p, mult_color(n_color, bright)));
	return (1);
}
