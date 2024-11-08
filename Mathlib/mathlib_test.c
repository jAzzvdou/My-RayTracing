/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathlib_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:35:17 by jbergfel          #+#    #+#             */
/*   Updated: 2024/11/07 22:46:44 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/mathlib.h"
#include <stdio.h>

int	main(void)
{
	t_vector a;
	t_vector b;
	t_vector c;
	t_vector d;
	t_matrix e;
	t_matrix f;
	t_matrix g;
	t_matrix h;

	a.x = 1;
	a.y = 2;
	a.z = 3;

	b.x = 4;
	b.y = 5;
	b.z = 6;

	c = vector_add(a, b);
	d = vector_subtract(a, b);

	printf("Vector Add: %f %f %f\n", c.x, c.y, c.z);
	printf("Vector Subtract: %f %f %f\n", d.x, d.y, d.z);

	e.matrix[0][0] = 13;
	e.matrix[0][1] = -2;
	e.matrix[0][2] = 11;
	e.matrix[1][0] = 6;
	e.matrix[1][1] = 9;
	e.matrix[1][2] = -23;
	e.matrix[2][0] = 1;
	e.matrix[2][1] = 0;
	e.matrix[2][2] = 4;

	f.matrix[0][0] = 9;
	f.matrix[0][1] = 8;
	f.matrix[0][2] = 7;
	f.matrix[1][0] = 6;
	f.matrix[1][1] = 5;
	f.matrix[1][2] = 4;
	f.matrix[2][0] = 3;
	f.matrix[2][1] = 2;
	f.matrix[2][2] = 1;

	g = matrix_add(e, f);
	h = matrix_subtract(e, f);

	int i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			printf("Matrix Add: %f\n", g.matrix[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			printf("Matrix Subtract: %f\n", h.matrix[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}
