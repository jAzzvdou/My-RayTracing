/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:24:53 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/19 23:47:01 by jazevedo         ###   ########.fr       */
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
	char	**line_spl;
	t_color	amb_color;

	line_spl = my_split(line, ' ');
	if (!valid_line_count(line_spl, 3)
		|| !valid_has_amb_color(w->amb.has_amb_color)
		|| !get_double(line_spl[1], &amb_ratio)
		|| !get_color(line_spl[2], &amb_color))
	{
		line_spl = memcard(line_spl, VECTOR, FREE, 0);
		return (err(RED, "amb parse ko\n", RESET), 0);
	}
	line_spl = memcard(line_spl, VECTOR, FREE, 0);
	w->amb.has_amb_color = 1;
	w->amb.amb_ratio = amb_ratio;
	w->amb.amb_color = amb_color;
	return (1);
}
