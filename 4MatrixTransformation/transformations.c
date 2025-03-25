/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:07:02 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:51:33 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_matrix	translation(double x, double y, double z)
{
	t_matrix	matrix;

	matrix = identity();
	set_index(&matrix, 3, 0, x);
	set_index(&matrix, 3, 1, y);
	set_index(&matrix, 3, 2, z);
	return (matrix);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	matrix;

	matrix = identity();
	set_index(&matrix, 0, 0, x);
	set_index(&matrix, 1, 1, y);
	set_index(&matrix, 2, 2, z);
	return (matrix);
}

t_matrix	shearing(double *x, double *y, double *z)
{
	t_matrix	matrix;

	matrix = identity();
	set_index(&matrix, 1, 0, x[0]);
	set_index(&matrix, 2, 0, x[1]);
	set_index(&matrix, 0, 1, y[0]);
	set_index(&matrix, 2, 1, y[1]);
	set_index(&matrix, 0, 2, z[0]);
	set_index(&matrix, 1, 2, z[1]);
	return (matrix);
}
