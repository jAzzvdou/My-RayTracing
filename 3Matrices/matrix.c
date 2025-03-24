/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:53:28 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/18 01:28:30 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

void	set_index(t_matrix *a, int x, int y, double value)
{
	if (x < 0 || x >= a->cols || y < 0 || y >= a->rows)
		return ;
	a->matrix[y * a->cols + x] = value;
}

double	get_index(t_matrix *a, int x, int y)
{
	if (x < 0 || x >= a->cols || y < 0 || y >= a->rows)
		return (0);
	return (a->matrix[y * a->cols + x]);
}

static double	mult_index(t_matrix a, t_matrix b, int x, int y)
{
	int	i;
	double	result;

	result = 0;
	i = 0;
	while (i < a.cols)
	{
		result += get_index(&a, i, y) * get_index(&b, x, i);
		i++;
	}
	return (result);
}

t_matrix	mult_matrix(t_matrix a, t_matrix b)
{
	int		x;
	int		y;
	t_matrix	matrix;

	my_bzero(&matrix, sizeof(t_matrix));
	if (a.rows != b.rows || a.cols != b.cols)
		return (matrix);
	matrix.rows = a.rows;
	matrix.cols = a.cols;
	y = 0;
	while (y < matrix.rows)
	{
		x = 0;
		while (x < matrix.cols)
		{
			set_index(&matrix, x, y, mult_index(a, b, x, y));
			x++;
		}
		y++;
	}
	return (matrix);
}

t_tuple	mult_matrix_tuple(t_matrix a, t_tuple b)
{
	t_tuple	result;

	result.x = get_index(&a, 0, 0) * b.x + get_index(&a, 1, 0) * b.y;
	result.x += get_index(&a, 2, 0) * b.z + get_index(&a, 3, 0) * b.w;
	result.y = get_index(&a, 0, 1) * b.x + get_index(&a, 1, 1) * b.y;
	result.y += get_index(&a, 2, 1) * b.z + get_index(&a, 3, 1) * b.w;
	result.z = get_index(&a, 0, 2) * b.x + get_index(&a, 1, 2) * b.y;
	result.z += get_index(&a, 2, 2) * b.z + get_index(&a, 3, 2) * b.w;
	result.w = get_index(&a, 0, 3) * b.x + get_index(&a, 1, 3) * b.y;
	result.w += get_index(&a, 2, 3) * b.z + get_index(&a, 3, 3) * b.w;
	return (result);
}
