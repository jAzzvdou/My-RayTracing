/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:54:39 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 01:22:06 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int     get_pattern_cylinder(char **splited, t_pattern *pattern)
{
        t_color a;
        t_color b;

        if (!my_strcmp(splited[9], "null") && !my_strcmp(splited[12], "null"))
                return (1);
        if (my_strcmp(splited[9], "null") && my_strcmp(splited[12], "null"))
                return (0);
        if (my_strcmp(splited[12], "null") && valid_path(splited[12]))
        {
                *pattern = new_pattern(TEXTURE, color(0, 0, 0), color(0, 0, 0));
                pattern->texture_path = my_strjoin("10Patterns/Textures/", splited[12]);
        }
        else if (!get_color(splited[10], &a) || !get_color(splited[11], &b))
                return (0);
        else if (!my_strcmp(splited[9], "stripe"))
                *pattern = new_pattern(STRIPE, a, b);
        else if (!my_strcmp(splited[9], "gradient"))
                *pattern = new_pattern(GRADIENT, a, b);
        else if (!my_strcmp(splited[9], "ring"))
                *pattern = new_pattern(RING, a, b);
        else if (!my_strcmp(splited[9], "checker"))
                *pattern = new_pattern(CHECKER, a, b);
        else
                return (0);
        return (1);
}

int	valid_cylinder(char **splited, t_point *p, t_vector *n, t_object *n_cy)
{
	if (!valid_line_count(splited, 13)
		|| !get_coords(splited[1], p)
		|| !get_dir(splited[2], n)
		|| !get_double(splited[3], &n_cy->radius)
		|| !get_double(splited[4], &n_cy->maximum)
		|| !get_color(splited[5], &n_cy->material.color)
		|| !get_transparency(splited[6], &n_cy->material.transparency)
		|| !get_reflective(splited[7], splited[8],
				&n_cy->material.reflective,
				&n_cy->material.refractive_index)
		|| !get_pattern_cylinder(splited, &n_cy->material.pattern))
		return (0);
	return (1);
}

int	cy_parse(t_world *w, char *line)
{
	char		**splited;
	t_point		p;
	t_vector	n;
	t_object	n_cy;

	n_cy = new_object(CY);
	splited = my_split(line, ' ');
	if (!valid_cylinder(splited, &p, &n, &n_cy))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! cylinder_parse ko\n", RESET), 0);
	}
	splited = memcard(splited, VECTOR, FREE, 0);
	n_cy.radius /= 2;
	n_cy.maximum /= n_cy.radius;
	n_cy.minimum = 0;
	n_cy.closed = false;
	set_transform(&n_cy, rotate_matrix(p, n, n_cy));
	add_object(&w->object, n_cy);
	return (1);
}
