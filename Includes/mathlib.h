/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:10:32 by jbergfel          #+#    #+#             */
/*   Updated: 2024/11/07 22:34:04 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHLIB_H
# define MATHLIB_H

# include <math.h>

typedef struct s_matrix
{
	double	matrix[3][3];
}	t_matrix;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_matrix	matrix_add(t_matrix a, t_matrix b);
t_matrix	matrix_subtract(t_matrix a, t_matrix b);
t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_matrix	matrix_divide(t_matrix a, t_matrix b);
t_matrix	matrix_scalar_multiply(t_matrix a, double scalar);

t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_multiply(t_vector a, t_vector b);
t_vector	vector_scalar(t_vector a, double scalar);

#endif
