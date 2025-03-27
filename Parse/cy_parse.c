/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:54:39 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/27 00:10:55 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_pattern_cylinder(char **splited, t_pattern *pattern, void *mlx)
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

int	valid_cy(char **split, t_point *p, t_object *n_cy, void *mlx)
{
	t_vector	n;

	if (!valid_line_count(split, 13)
		|| !get_coords(split[1], p)
		|| !get_dir(split[2], &n)
		|| !get_double(split[3], &n_cy->radius)
		|| !get_double(split[4], &n_cy->maximum)
		|| !get_color(split[5], &n_cy->material.color)
		|| !get_transparency(split[6], &n_cy->material.transparency)
		|| !get_reflective(split[7], split[8],
			&n_cy->material.reflective,
			&n_cy->material.refractive_index)
		|| !get_pattern_cylinder(split, &n_cy->material.pattern, mlx))
		return (0);
	n_cy->normal = n;
	return (1);
}

int	cy_parse(t_world *w, char *line, void *mlx)
{
	char		**splited;
	t_object	n_cy;
	t_point		p;

	n_cy = new_object(CY);
	splited = my_split(line, ' ');
	if (!valid_cy(splited, &p, &n_cy, mlx))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! cylinder_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_cy.radius /= 2;
	n_cy.maximum /= n_cy.radius;
	n_cy.minimum = 0;
	n_cy.closed = false;
	set_transform(&n_cy, rotate_matrix(p, n_cy.normal, n_cy));
	add_object(&w->object, n_cy);
	return (1);
}
