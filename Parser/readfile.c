/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:11:43 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:09 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_rgb(char *line)
{
	size_t		rgb[3];
	char	**split;

	split = splitline(line, ',');
	if (matrixlen(split) != 3)
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	rgb[0] = (size_t)ft_atoi(split[0]);
	rgb[1] = (size_t)ft_atoi(split[1]);
	rgb[2] = (size_t)ft_atoi(split[2]);
	split = memcard(split, VECTOR, FREE, 0);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (1);
	return (0);
}	

t_map	*start_map(void)
{
	t_map	*map;

	map = memcard(NULL, DEFAULT, MALLOC, sizeof(t_map));
	if (!map)
		return (NULL);
	map->a = NULL;
	map->c = NULL;
	map->l = NULL;
	map->pl = NULL;
	map->sp = NULL;
	map->cy = NULL;
	return (map);
}

int	add_map(t_map *map, char *line)
{
	int	valid;

	valid = 0;
	if (!ft_strncmp(line, "A ", 2))
		valid = add_ambient(map, line);
	/*else if (!ft_strncmp(line, "C ", 2))
		valid = add_camera(map, line);
	else if (!ft_strncmp(line, "L ", 2))
		valid = add_light(map, line);
	else if (!ft_strncmp(line, "pl ", 3))
		valid = add_plane(map, line);
	else if (!ft_strncmp(line, "sp ", 3))
		valid = add_sphere(map, line);
	else if (!ft_strncmp(line, "cy ", 3))
		valid = add_cylinder(map, line);*/
	if (valid)
		return (1);
	err(RED, INVALID_VARIABLE, RESET);
	return (memcard(NULL, 0, FREEALL, 0), 0);
}

t_map	*readfile(char *file)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		err(RED, INVALID_FILE, RESET);
		return (memcard(NULL, 0, FREEALL, 0), NULL);
	}
	map = start_map();
	line = get_next_line(fd);
	while (line)
	{
		skip_spaces(&line);
		if (*line)
			if (!add_map(map, line))
				return (NULL);
		line = memcard(line, STRING, FREE, 0);
		line = get_next_line(fd);
	}
	return (map);
}
