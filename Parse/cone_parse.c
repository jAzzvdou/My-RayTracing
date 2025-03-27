/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:34:43 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/27 00:11:17 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_pattern_cone(char **splited, t_pattern *pattern, void *mlx)
{
	t_color	ab[2];

	ab[0] = color(0, 0, 0);
	ab[1] = color(0, 0, 0);
	if (!my_strcmp(splited[9], "null") && !my_strcmp(splited[12], "null"))
		return (1);
	if (my_strcmp(splited[9], "null") && my_strcmp(splited[12], "null"))
		return (0);
	if (my_strcmp(splited[12], "null") && valid_path(splited[12]))
		*pattern = new_pattern(TEXTURE, ab,
				my_strjoin("10Patterns/Textures/", splited[12]), mlx);
	else if (!get_color(splited[10], &ab[0]) || !get_color(splited[11], &ab[1]))
		return (0);
	else if (!my_strcmp(splited[9], "stripe"))
		*pattern = new_pattern(STRIPE, ab, NULL, mlx);
	else if (!my_strcmp(splited[9], "gradient"))
		*pattern = new_pattern(GRADIENT, ab, NULL, mlx);
	else if (!my_strcmp(splited[9], "ring"))
		*pattern = new_pattern(RING, ab, NULL, mlx);
	else if (!my_strcmp(splited[9], "checker"))
		*pattern = new_pattern(CHECKER, ab, NULL, mlx);
	else
		return (0);
	return (1);
}

int	valid_cone(char **split, t_point *p, t_object *n_cn, void *mlx)
{
	t_point	n;

	if (!valid_line_count(split, 13)
		|| !get_coords(split[1], p)
		|| !get_dir(split[2], &n)
		|| !get_double(split[3], &n_cn->radius)
		|| !get_double(split[4], &n_cn->maximum)
		|| !get_color(split[5], &n_cn->material.color)
		|| !get_transparency(split[6], &n_cn->material.transparency)
		|| !get_reflective(split[7], split[8], &n_cn->material.reflective,
			&n_cn->material.refractive_index)
		|| !get_pattern_cone(split, &n_cn->material.pattern, mlx))
		return (0);
	n_cn->normal = n;
	return (1);
}

int	cone_parse(t_world *w, char *line, void *mlx)
{
	char		**splited;
	t_object	n_cn;
	t_point		p;

	n_cn = new_object(CN);
	splited = my_split(line, ' ');
	if (!valid_cone(splited, &p, &n_cn, mlx))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! cone_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_cn.radius /= 2;
	n_cn.maximum /= 2;
	n_cn.maximum /= n_cn.radius;
	n_cn.minimum = -n_cn.maximum;
	n_cn.closed = true;
	set_transform(&n_cn, rotate_matrix(p, n_cn.normal, n_cn));
	add_object(&w->object, n_cn);
	return (1);
}
