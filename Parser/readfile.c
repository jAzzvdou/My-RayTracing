/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:11:43 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/09 11:50:55 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

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
	if (line[0] == 'A' && is_space(line[1]))
		valid = add_ambient(map, line);
	else if (line[0] == 'C' && is_space(line[1]))
		valid = add_camera(map, line);
	else if (line[0] == 'L' && is_space(line[1]))
		valid = add_light(map, line);
	else if (!my_strncmp(line, "sp", 2) && is_space(line[2]))
		valid = add_sphere(map, line);
	else if (!my_strncmp(line, "pl", 2) && is_space(line[2]))
		valid = add_plane(map, line);
	else if (!my_strncmp(line, "cy", 2) && is_space(line[2]))
		valid = add_cylinder(map, line);
	if (valid)
		return (1);
	err(RED, INVALID_CONFIG, RESET);
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
