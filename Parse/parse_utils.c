/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:47:46 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:21:57 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	valid_path(char *s)
{
	int		fd;
	char	*path;

	path = my_strjoin("10Patterns/Textures/", s);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	path = memcard(path, STRING, FREE, 0);
	return (1);
}

int	valid_line_count(char **str_split, int words_to_go)
{
	int	words;

	words = 0;
	while (str_split[words])
		words++;
	if (words != words_to_go)
		return (0);
	return (1);
}

int	get_int(char *str, int *n)
{
	int	i;

	i = 0;
	while (str && str[i] && my_isdigit(str[i]))
		i++;
	if (!str || str[i] != '\0')
	{
		err(RED, "Error! get_int ko\n", RESET);
		if (str)
			err(RED, str, RESET);
		else
			err(RED, "NULL", RESET);
		return (0);
	}
	*n = my_atoi(str);
	return (1);
}

int	get_double(char *str, double *val)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '.')
		return (0);
	if (str[i] == '-' && my_isdigit(str[i + 1]))
		i++;
	while (str[i] && my_isdigit(str[i]))
		i++;
	if (str[i] == '.' && my_isdigit(str[i + 1]))
		i++;
	else if (str[i] && !my_isdigit(str[i]))
		return (0);
	while (str[i] && my_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	*val = my_atod(str);
	return (1);
}
