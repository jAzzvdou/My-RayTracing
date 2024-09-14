/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:46:46 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/14 20:27:38 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_ambient(char **split)
{
	double	amblight;

	if (matrixlen(split) != 3)
		return (1);
	if (ft_strcmp(split[0], "A"))
		return (1);
	amblight = ft_atod(split[1]);
	if (amblight < 0 || amblight > 1)
		return (1);
	if (invalid_rgb(split[2]))
		return (1);
	return (0);
}

int	add_ambient(t_map *map, char *line)
{
	char	**split;
	char	**color;
	t_amb	*amb;

	split = splitline(line, ' ');
	if (!split || invalid_ambient(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	amb = memcard(NULL, DEFAULT, MALLOC, sizeof(t_amb));
	amb->type = A;
	amb->amblight = ft_atod(split[1]);
	color = splitline(split[2], ',');
	amb->rgb[0] = color[0];
	amb->rgb[1] = color[1];
	amb->rgb[2] = color[2];
	return (1);
}
