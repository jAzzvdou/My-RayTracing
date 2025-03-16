/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:47:46 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/15 23:21:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

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
		printf("ERROR get int\n");
		if (str)
			printf("Error get int str\n");
		else
			printf("NULL\n");
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
	if (!valid_line_count(str_split, 3) || !get_double(str_split[0], &position->x) || !get_double(str_split[1], &position->y) || !get_double(str_split[2], &position->z))
	{
		//split free
		printf("get_coords ko\n");
		return (0);
	}
	//split free
	position->w = 1;
	return (1);
}

int	get_directions(char *str, t_vector *dir)
{
	char	**str_split;

	str_split = my_split(str, ',');
	if (!valid_line_count(str_split, 3) || !get_double(str_split[0], &dir->x) || !get_double(str_split[1], &dir->y) || !get_double(str_split[2], &dir->z))
	{
		//split free
		printf("get_directions ko\n");
		return (0);
	}
	//split free
	dir->w = 1;
	return (1);
}

int	valid_colors(char **spl, int *r, int *g, int *b)
{
	if (!get_int(spl[0], r) || !get_int(spl[1], g) || !get_int(spl[2], b))
		return (printf("get_int colors ko\n"), 0);
	if (!(*r >= 0 && *r <= 255) || !(*g >= 0 && *g <= 255) || !(*b >= 0 && *b <= 255))
		return (printf("color limits ko\n"), 0);
	return (1);
}

int	get_color(char *str, t_color *n_color)
{
	int		r;
	int		g;
	int		b;
	char	**str_split;

	str_split = my_split(str, ',');
	if (!valid_line_count(str_split, 3) || !valid_colors(str_split, &r, &g, &b))
	{
		//split free
		return (printf("get_color ko\n"), 0);
	}
	n_color->r = r;
	n_color->g = g;
	n_color->b = b;
	*n_color = convert_color(*n_color);

	printf("r -> %f\n", n_color->r);
	printf("g -> %f\n", n_color->g);
	printf("b -> %f\n", n_color->b);
	return (1);
}
