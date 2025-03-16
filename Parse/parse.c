/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:24:57 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/15 23:25:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_line_token(char *line)
{
	if (!line)
		return (0);
	else if (my_strncmp(line, "A ", 2) == 0)
		return (A);
	else if (my_strncmp(line, "C ", 2) == 0)
		return (C);
	else if (my_strncmp(line, "L ", 2) == 0)
		return (L);
	else if (my_strncmp(line, "sp ", 3) == 0)
		return (SP);
	else if (my_strncmp(line, "pl ", 3) == 0)
		return (PL);
	else if (my_strncmp(line, "cy", 3) == 0)
		return (CY);
	else if (my_strncmp(line, "cn ", 3) == 0)
		return (CN);
	else if (my_strncmp(line, "P ", 2) == 0)
		return (P);
	else if (my_strncmp(line, "m ", 2) == 0)
		return (MT);
	return (0);
}

int	parse_line(char *line, t_world *w)
{
	int	token;

	token = get_line_token(line);
	if (!line[0] || line[0] == '\n' || line[0] == '#')
		return (1);
	else if (!token)
		return (0);
	/*if (token == A)
		return (amb_parse(w, line));*/
	if (token == C)
		return (cam_parse(w, line));
	else if (token == L)
		return (light_parse(w, line));
	else if (token == SP)
		return (sphere_parse(w, line));

	return (1);
}

int	parse(int fd, t_world *w)
{
	int		line_count;
	char	*line;

	line_count = 1;
	*w = world();
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (my_strchr(line, '\n'))
			my_strchr(line, '\n')[0] = '\0';
		if (!parse_line(line, w))
		{
			printf("line error -> %i\n", line_count);
			return (0);
		}
		//printf("line %i -> %s\n", line_count, line);
		//free(line);
		line = get_next_line(fd);
		line_count++;
	}
	return (1);
}
