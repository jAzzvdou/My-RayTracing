/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:17:18 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:20:33 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

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
