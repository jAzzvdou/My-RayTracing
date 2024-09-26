/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:38 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 12:28:53 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_sphere(char **split)
{
	if (matrixlen(split) != 4)
		return (1);
	if (ft_strcmp(split[0], "sp"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	if (!onlynumber(split[2], DOUBLE) || ft_atod(split[2]) < 0)
		return (1);
	if (invalid_rgb(split[3]))
		return (1);
	return (0);
}

t_sphere	*fill_sphere(char **split)
{
	char		**tmp;
	t_sphere	*sphere;

	sphere = memcard(NULL, DEFAULT, MALLOC, sizeof(t_sphere));
	sphere->type = SP;
	tmp = splitline(split[1], ',');
	sphere->coord[0] = ft_atod(tmp[0]);
	sphere->coord[1] = ft_atod(tmp[1]);
	sphere->coord[2] = ft_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	sphere->diameter = ft_atod(split[2]);
	tmp = splitline(split[3], ',');
	sphere->rgb[0] = ft_atoi(tmp[0]);
	sphere->rgb[1] = ft_atoi(tmp[1]);
	sphere->rgb[2] = ft_atoi(tmp[2]);
	return (tmp = memcard(tmp, VECTOR, FREE, 0), sphere);
}

int	add_sphere(t_map *map, char *line)
{
	char		**split;

	split = splitline(line, '\0');
	if (invalid_sphere(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	map->sp = fill_sphere(split);
	return (split = memcard(split, VECTOR, FREE, 0), 1);
}	
