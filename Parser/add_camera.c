/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:47:03 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/17 10:55:41 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

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
