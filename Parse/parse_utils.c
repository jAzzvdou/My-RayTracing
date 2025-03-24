/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:47:46 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/24 20:00:46 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_transparency(char *s, double *transparency)
{
	*transparency = my_atod(s);
	if (*transparency < 0 || *transparency > 1)
		return (0);
	return (1);
}

int	get_reflective(char *s1, char *s2, double *reflective, double *refractive_index)
{
	*reflective = my_atod(s1);
	*refractive_index = my_atod(s2);
	if (*reflective < 0 || *reflective > 1
		|| *refractive_index < 0 || *refractive_index > 20)
		return (0);
	return (1);
}

int	valid_path(char *s)
{
	int	fd;
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

int	get_coords(char *str, t_point *position)
{
	char	**str_split;

	str_split = my_split(str, ',');
	if (!valid_line_count(str_split, 3)
		|| !get_double(str_split[0], &position->x)
		|| !get_double(str_split[1], &position->y)
		|| !get_double(str_split[2], &position->z))
	{
		str_split = memcard(str_split, VECTOR, FREE, 0);
		return (err(RED, "Error! get_coords ko\n", RESET), 0);
	}
	str_split = memcard(str_split, VECTOR, FREE, 0);
	position->w = 1;
	return (1);
}

int	get_dir(char *str, t_vector *dir)
{
	char	**str_split;

	str_split = my_split(str, ',');
	if (!valid_line_count(str_split, 3)
		|| !get_double(str_split[0], &dir->x)
		|| !get_double(str_split[1], &dir->y)
		|| !get_double(str_split[2], &dir->z))
	{
		str_split = memcard(str_split, VECTOR, FREE, 0);
		return (err(RED, "Error! get_dir ko\n", RESET), 0);
	}
	str_split = memcard(str_split, VECTOR, FREE, 0);
	dir->w = 1;
	return (1);
}

int	valid_colors(char **spl, int *r, int *g, int *b)
{
	if (!get_int(spl[0], r) || !get_int(spl[1], g) || !get_int(spl[2], b))
		return (err(RED, "Error! get_int colors ko\n", RESET), 0);
	if (!(*r >= 0 && *r <= 255)
		|| !(*g >= 0 && *g <= 255)
		|| !(*b >= 0 && *b <= 255))
		return (err(RED, "Error! color limits ko\n", RESET), 0);
	return (1);
}

int	get_color(char *str, t_color *n_color)
{
	int		r;
	int		g;
	int		b;
	char	**str_split;

	str_split = my_split(str, ',');
	if (!valid_line_count(str_split, 3)
		|| !valid_colors(str_split, &r, &g, &b))
	{
		str_split = memcard(str_split, VECTOR, FREE, 0);
		return (err(RED, "Error! get_color ko\n", RESET), 0);
	}
	str_split = memcard(str_split, VECTOR, FREE, 0);
	n_color->r = r;
	n_color->g = g;
	n_color->b = b;
	*n_color = convert_color(*n_color);
	return (1);
}

int	get_radius(char *str, double *r)
{
	if (!get_double(str, r) || !(*r > 0))
		return (err(RED, "Erro! get radius ko\n", RESET), 0);
	return (1);
}
