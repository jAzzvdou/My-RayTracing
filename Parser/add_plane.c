/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:32 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 13:52:01 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_plane(char **split)
{
	if (matrixlen(split) != 4)
		return (1);
	if (ft_strcmp(split[0], "pl"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	if (invalid_vector(split[2]))
		return (1);
	if (invalid_rgb(split[3]))
		return (1);
	return (0);
}

t_plane	*fill_plane(char **split)
{
	char	**tmp;
	t_plane	*plane;

	plane = memcard(NULL, DEFAULT, MALLOC, sizeof(t_plane));
	plane->type = PL;
	tmp = splitline(split[1], ',');
	plane->coord[0] = ft_atod(tmp[0]);
	plane->coord[1] = ft_atod(tmp[1]);
	plane->coord[2] = ft_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	tmp = splitline(split[2], ',');
	plane->nvector[0] = ft_atod(tmp[0]);
	plane->nvector[1] = ft_atod(tmp[1]);
	plane->nvector[2] = ft_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	tmp = splitline(split[3], ',');
	plane->rgb[0] = ft_atoi(tmp[0]);
	plane->rgb[1] = ft_atoi(tmp[1]);
	plane->rgb[2] = ft_atoi(tmp[2]);
	return (tmp = memcard(tmp, VECTOR, FREE, 0), plane);
}

int	add_plane(t_map *map, char *line)
{
	char	**split;

	split = splitline(line, '\0');
	if (invalid_plane(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	map->pl = fill_plane(split);
	return (split = memcard(split, VECTOR, FREE, 0), 1);
}
