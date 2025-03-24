/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:26:13 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/24 20:03:20 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_pattern_sphere(char **splited, t_pattern *pattern)
{
	t_color	a;
	t_color	b;

	if (!my_strcmp(splited[7], "null") && !my_strcmp(splited[10], "null"))
		return (1);
	if (my_strcmp(splited[7], "null") && my_strcmp(splited[10], "null"))
		return (0);
	if (my_strcmp(splited[10], "null") && valid_path(splited[10]))
	{
		*pattern = new_pattern(TEXTURE, color(0, 0, 0), color(0, 0, 0));
		pattern->texture_path = my_strjoin("10Patterns/Textures/", splited[10]);
	}
	else if (!get_color(splited[8], &a) || !get_color(splited[9], &b))
		return (0);
	else if (!my_strcmp(splited[7], "stripe"))
		*pattern = new_pattern(STRIPE, a, b);
	else if (!my_strcmp(splited[7], "gradient"))
		*pattern = new_pattern(GRADIENT, a, b);
	else if (!my_strcmp(splited[7], "ring"))
		*pattern = new_pattern(RING, a, b);
	else if (!my_strcmp(splited[7], "checker"))
		*pattern = new_pattern(CHECKER, a, b);
	else
		return (0);
	return (1);
}

int	valid_sphere(char **splited, t_point *p, t_object *n_sp)
{
	if (!valid_line_count(splited, 11)
		|| !get_coords(splited[1], p)
		|| !get_radius(splited[2], &n_sp->radius)
		|| !get_color(splited[3], &n_sp->material.color)
		|| !get_transparency(splited[4], &n_sp->material.transparency)
		|| !get_reflective(splited[5], splited[6],
			&n_sp->material.reflective,
			&n_sp->material.refractive_index)
		|| !get_pattern_sphere(splited, &n_sp->material.pattern))
		return (0);
	return (1);
}

int	sphere_parse(t_world *w, char *line)
{
	char		**splited;
	t_point		p;
	t_object	n_sp;

	n_sp = new_object(SP);
	splited = my_split(line, ' ');
	if (!valid_sphere(splited, &p, &n_sp))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! sphere_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_sp.radius /= 2;
	set_transform(&n_sp, rotate_matrix(p, point(0, 1, 0), n_sp));
	add_object(&w->object, n_sp);
	return (1);
}
