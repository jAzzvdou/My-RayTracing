/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:46:35 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/27 00:11:44 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_pattern_plane(char **splited, t_pattern *pattern, void *mlx)
{
	t_color	ab[2];

	ab[0] = color(0, 0, 0);
	ab[1] = color(0, 0, 0);
	if (!my_strcmp(splited[7], "null") && !my_strcmp(splited[10], "null"))
		return (1);
	if (my_strcmp(splited[7], "null") && my_strcmp(splited[10], "null"))
		return (0);
	if (my_strcmp(splited[10], "null") && valid_path(splited[10]))
		*pattern = new_pattern(TEXTURE, ab,
				my_strjoin("10Patterns/Textures/", splited[10]), mlx);
	else if (!get_color(splited[8], &ab[0]) || !get_color(splited[9], &ab[1]))
		return (0);
	else if (!my_strcmp(splited[7], "stripe"))
		*pattern = new_pattern(STRIPE, ab, NULL, mlx);
	else if (!my_strcmp(splited[7], "gradient"))
		*pattern = new_pattern(GRADIENT, ab, NULL, mlx);
	else if (!my_strcmp(splited[7], "ring"))
		*pattern = new_pattern(RING, ab, NULL, mlx);
	else if (!my_strcmp(splited[7], "checker"))
		*pattern = new_pattern(CHECKER, ab, NULL, mlx);
	else
		return (0);
	return (1);
}

int	valid_pl(char **split, t_point *p, t_object *n_pl, void *mlx)
{
	t_vector	n;

	if (!valid_line_count(split, 11)
		|| !get_coords(split[1], p)
		|| !get_dir(split[2], &n)
		|| !get_color(split[3], &n_pl->material.color)
		|| !get_transparency(split[4], &n_pl->material.transparency)
		|| !get_reflective(split[5], split[6], &n_pl->material.reflective,
			&n_pl->material.refractive_index)
		|| !get_pattern_plane(split, &n_pl->material.pattern, mlx))
		return (0);
	n_pl->normal = n;
	return (1);
}

int	plane_parse(t_world *w, char *line, void *mlx)
{
	char		**splited;
	t_object	n_pl;
	t_point		p;

	n_pl = new_object(PL);
	splited = my_split(line, ' ');
	if (!valid_pl(splited, &p, &n_pl, mlx))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! plane_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	set_transform(&n_pl, rotate_matrix(p, n_pl.normal, n_pl));
	add_object(&w->object, n_pl);
	return (1);
}
