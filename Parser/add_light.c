/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:25 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 13:51:41 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_light(char **split)
{
	double	brightness;

	if (matrixlen(split) != 4)
		return (1);
	if (my_strcmp(split[0], "L"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	if (!onlynumber(split[2], DOUBLE))
		return (1);
	brightness = my_atod(split[2]);
	if (brightness < 0 || brightness > 1)
		return (1);
	if (invalid_rgb(split[3]))
		return (1);
	return (0);
}

t_light	*fill_light(char **split)
{
	char	**tmp;
	t_light	*light;

	light = memcard(NULL, DEFAULT, MALLOC, sizeof(t_light));
	light->type = L;
	tmp = splitline(split[1], ',');
	light->coord[0] = my_atod(tmp[0]);
	light->coord[1] = my_atod(tmp[1]);
	light->coord[2] = my_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	light->brightness = my_atod(split[2]);
	tmp = splitline(split[3], ',');
	light->rgb[0] = my_atoi(tmp[0]);
	light->rgb[1] = my_atoi(tmp[1]);
	light->rgb[2] = my_atoi(tmp[2]);
	return (tmp = memcard(tmp, VECTOR, FREE, 0), light);
}

int	add_light(t_map *map, char *line)
{
	char	**split;

	split = splitline(line, '\0');
	if (invalid_light(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	map->l = fill_light(split);
	return (split = memcard(split, VECTOR, FREE, 0), 1);
}
