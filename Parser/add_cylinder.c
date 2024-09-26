/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:18 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 12:38:31 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_cylinder(char **split)
{
	if (matrixlen(split) != 6)
		return (1);
	if (ft_strcmp(split[0], "cy"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	if (invalid_vector(split[2]))
		return (1);
	if (!onlynumber(split[3], DOUBLE) || ft_atod(split[3]) < 0)
		return (1);
	if (!onlynumber(split[4], DOUBLE) || ft_atod(split[4]) < 0)
		return (1);
	if (invalid_rgb(split[5]))
		return (1);
	return (0);
}

t_cylinder	*fill_cylinder(char **split)
{
	char		**tmp;
	t_cylinder	*cylinder;

	cylinder = memcard(NULL, DEFAULT, MALLOC, sizeof(t_cylinder));
	cylinder->type = CY;
	tmp = splitline(split[1], ',');
	cylinder->coord[0] = ft_atod(tmp[0]);
	cylinder->coord[1] = ft_atod(tmp[1]);
	cylinder->coord[2] = ft_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	tmp = splitline(split[2], ',');
	cylinder->nvector[0] = ft_atod(tmp[0]);
	cylinder->nvector[1] = ft_atod(tmp[1]);
	cylinder->nvector[2] = ft_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	tmp = splitline(split[5], ',');
	cylinder->rgb[0] = ft_atoi(tmp[0]);
	cylinder->rgb[1] = ft_atoi(tmp[1]);
	cylinder->rgb[2] = ft_atoi(tmp[2]);
	return (tmp = memcard(tmp, VECTOR, FREE, 0), cylinder);
}

int	add_cylinder(t_map *map, char *line)
{
	char		**split;

	split = splitline(line, '\0');
	if (invalid_cylinder(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	map->cy = fill_cylinder(split);
	return (split = memcard(split, VECTOR, FREE, 0), 1);
}
