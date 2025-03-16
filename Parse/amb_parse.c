/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:24:53 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/16 11:32:34 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	valid_has_amb_color(int has_ambient_color)
{
	if (has_ambient_color == 0)
		return (1);
	printf("Error has ambient color already\n");
	return (0);
}

int	amb_parse(t_world *w, char *line)
{
	double	amb_ratio;
	t_color	amb_color;
	char	**line_spl;

	printf("----------AMB PARSE----------\n");
	line_spl = my_split(line, ' ');
	if (!valid_line_count(line_spl, 3) || !valid_has_amb_color(w->amb.has_amb_color) || !get_double(line_spl[1], &amb_ratio) || !get_color(line_spl[2], &amb_color))
	{
		printf("amb parse ko\n");
		//split free
		return (0);
	}
	//split free
	w->amb.has_amb_color = 1;
	w->amb.amb_ratio = amb_ratio;
	printf("Amb ratio -> %f\n", w->amb.amb_ratio);
	w->amb.amb_color = amb_color;
	printf("amb parse ok\n\n");
	return (1);
}

