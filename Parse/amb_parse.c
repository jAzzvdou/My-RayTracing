/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:24:53 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/24 11:07:05 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	valid_has_amb_color(int has_ambient_color)
{
	if (!has_ambient_color)
		return (1);
	err(RED, "Error! Has ambient color already\n", RESET);
	return (0);
}

int	amb_parse(t_world *w, char *line)
{
	double		amb_ratio;
	char	**splited;
	t_color	amb_color;

	splited = my_split(line, ' ');
	if (!valid_line_count(splited, 3)
		|| !valid_has_amb_color(w->amb.has_amb_color)
		|| !get_double(splited[1], &amb_ratio)
		|| !get_color(splited[2], &amb_color))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "amb parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	w->amb.has_amb_color = 1;
	w->amb.amb_ratio = amb_ratio;
	w->amb.amb_color = amb_color;
	return (1);
}
