/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:46:35 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 15:42:34 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_pattern_plane(char **splited, t_pattern *pattern, void *mlx)
{
	t_color	a;
	t_color	b;

	if (!my_strcmp(splited[7], "null") && !my_strcmp(splited[10], "null"))
		return (1);
	if (my_strcmp(splited[7], "null") && my_strcmp(splited[10], "null"))
		return (0);
	if (my_strcmp(splited[10], "null") && valid_path(splited[10]))
		*pattern = new_pattern(TEXTURE, color(0, 0, 0), color(0, 0, 0),
				my_strjoin("10Patterns/Textures/", splited[10]), mlx);
	else if (!get_color(splited[8], &a) || !get_color(splited[9], &b))
		return (0);
	else if (!my_strcmp(splited[7], "stripe"))
		*pattern = new_pattern(STRIPE, a, b, NULL, mlx);
	else if (!my_strcmp(splited[7], "gradient"))
		*pattern = new_pattern(GRADIENT, a, b, NULL, mlx);
	else if (!my_strcmp(splited[7], "ring"))
		*pattern = new_pattern(RING, a, b, NULL, mlx);
	else if (!my_strcmp(splited[7], "checker"))
		*pattern = new_pattern(CHECKER, a, b, NULL, mlx);
	else
		return (0);
	return (1);
}

int	valid_pl(char **split, t_point *p, t_vector *n, t_object *n_pl, void *mlx)
{
	if (!valid_line_count(split, 11)
		|| !get_coords(split[1], p)
		|| !get_dir(split[2], n)
		|| !get_color(split[3], &n_pl->material.color)
		|| !get_transparency(split[4], &n_pl->material.transparency)
		|| !get_reflective(split[5], split[6], &n_pl->material.reflective,
			&n_pl->material.refractive_index)
		|| !get_pattern_plane(split, &n_pl->material.pattern, mlx))
		return (0);
	return (1);
}

int	plane_parse(t_world *w, char *line, void *mlx)
{
	char		**splited;
	t_point		p;
	t_vector	n;
	t_object	n_pl;

	n_pl = new_object(PL);
	splited = my_split(line, ' ');
	if (!valid_pl(splited, &p, &n, &n_pl, mlx))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! plane_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_pl.normal = n;
	n_pl.origin = p;
	set_transform(&n_pl, rotate_matrix(p, n, n_pl));
	add_object(&w->object, n_pl);
	return (1);
}
