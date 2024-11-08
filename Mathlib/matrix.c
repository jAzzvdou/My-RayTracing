/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:10:20 by jbergfel          #+#    #+#             */
/*   Updated: 2024/11/07 22:43:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/mathlib.h"

t_matrix	matrix_add(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix	matrix_subtract(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix	matrix_divide(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result.matrix[i][j] = a.matrix[i][j] / b.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			result.matrix[i][j] = 0;
			while (k < 3)
			{
				result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix	matrix_scalar_multiply(t_matrix a, double scalar)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result.matrix[i][j] = a.matrix[i][j] * scalar;
			j++;
		}
		i++;
	}
	return (result);
}
