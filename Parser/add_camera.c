/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:03 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/17 11:54:39 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_camera(char **split)
{
	size_t	fov;

	if (matrixlen(split) != 3)
		return (1);
	if (ft_strcmp(split[0], "C"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	if (invalid_vector(split[2]))
		return (1);
	fov = (size_t)ft_atoi(split[3]);
	if (fov > 180)
		return (1);
	return (0);
}

int	add_camera(t_map *map, char *line)
{
	char	**split;
	char	**tmp;
	t_cam	*cam;

	split = splitline(line ' ');
	if (invalid_camera(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	cam = memcard(NULL, DEFAULT, MALLOC, sizeof(t_camera));
	cam->type = C;
	tmp = splitline(split[1], ',');
	cam->coord[0] = ft_atod(tmp[0]);
	cam->coord[1] = ft_atod(tmp[1]);
	cam->coord[2] = ft_atod(tmp[2]);
	tmp = memcard(coord, VECTOR, FREE, 0);
	tmp = splitline(split[2], ',');
	cam->nvector[0] = ft_atod(tmp[0]);
	cam->nvector[1] = ft_atod(tmp[1]);
	cam->nvector[2] = ft_atod(tmp[2]);
	tmp = memcard(coord, VECTOR, FREE, 0);
	cam->fov = ft_atoi(split[3]);
	split = memcard(split, VECTOR, FREE, 0);
	map->c = cam;
	return (1);
}
