/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:03 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/14 06:06:31 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_camera(char **split)
{
	int	fov;

	if (matrixlen(split) != 4)
		return (1);
	if (my_strcmp(split[0], "C"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	if (invalid_vector(split[2]))
		return (1);
	fov = my_atoi(split[3]);
	if (fov < 0 || fov > 180)
		return (1);
	return (0);
}

t_cam	*fill_camera(char **split)
{
	char	**tmp;
	t_cam	*cam;

	cam = memcard(NULL, DEFAULT, MALLOC, sizeof(t_cam));
	cam->type = C;
	tmp = splitline(split[1], ',');
	cam->coord.x = my_atod(tmp[0]);
	cam->coord.y = my_atod(tmp[1]);
	cam->coord.z = my_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	tmp = splitline(split[2], ',');
	cam->orientation.x = my_atod(tmp[0]);
	cam->orientation.y = my_atod(tmp[1]);
	cam->orientation.z = my_atod(tmp[2]);
	tmp = memcard(tmp, VECTOR, FREE, 0);
	cam->fov = my_atod(split[3]);
	cam->scale = tan((cam->fov / 2) * PI / 180.0);
	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam->right = vector_normalize(vector_cross(copy_vector(0, 1, 0), cam->orientation));
	cam->up = vector_normalize(vector_cross(cam->orientation, cam->right));
	return (cam);
}

int	add_camera(t_map *map, char *line)
{
	char	**split;

	split = splitline(line, '\0');
	if (invalid_camera(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	map->c = fill_camera(split);
	return (split = memcard(split, VECTOR, FREE, 0), 1);
}
