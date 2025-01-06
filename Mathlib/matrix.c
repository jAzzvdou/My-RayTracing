/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:52:27 by joao              #+#    #+#             */
/*   Updated: 2025/01/05 21:21:04 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"


t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 16)
		*(*(result.m) + i) = 0;
	i = -1;
	while(++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			result.m[i][j] = 0;
			k = -1;
			while (++k < 4)
			{
				result.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return (result);
}

t_matrix	matrix_rotate_x(double degree)
{
	static	t_matrix	result;

	result.m[0][0] = 1.0;
	result.m[1][1] = cos(radian(degree));
	result.m[1][2] = -sin(radian(degree));
	result.m[2][1] = sin(radian(degree));
	result.m[2][2] = cos(radian(degree));
	result.m[3][3] = 1.0;
}

t_matrix	matrix_rotate_y(double degree)
{
	static	t_matrix	result;

	result.m[0][0] = cos(radian(degree));
	result.m[0][2] = -sin(radian(degree));
	result.m[1][2] = 1.0;
	result.m[2][0] = sin(radian(degree));
	result.m[2][2] = cos(radian(degree));
	result.m[3][3] = 1.0;
	return (result);
}

t_matrix	matrix_rotate_z(double degree)
{
	static	t_matrix	result;

	result.m[0][0] = cos(radian(degree));
	result.m[0][1] = -sin(radian(degree));
	result.m[1][0] = sin(radian(degree));
	result.m[1][1] = cos(radian(degree));
	result.m[2][2] = 1.0;
	result.m[3][3] = 1.0;
	return (result);
}

double	radian(double degree)
{
	return (degree / 180.0 * PI);
}
