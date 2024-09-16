/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:03 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/16 17:55:02 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_coord(char *line)
{
	char	**split;

	split = splitline(line, ',');
	if (matrixlen(split) != 3)
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	if (!onlynumber(split[0]) || !onlynumber(split[1])
		|| !onlynumber(split[2]))
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	return (split = memcard(split, VECTOR, FREE, 0), 0);
}

int	invalid_camera(char **split)
{
	if (matrixlen(split) != 3)
		return (1);
	if (ft_strcmp(split[0], "C"))
		return (1);
	if (invalid_coord(split[1]))
		return (1);
	//| Fazer o resto das verificações.
	return (0);
}

int	add_camera(t_map *map, char *line)
{
	char	**split;
	t_cam	*cam;

	split = splitline(line ' ');
	if (invalid_camera(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	cam = memcard(NULL, DEFAULT, MALLOC, sizeof(t_camera));
	amb->type = C;
	//| Adicionar o restante na struct da câmera.
	map->c = cam;
	return (1);
}
