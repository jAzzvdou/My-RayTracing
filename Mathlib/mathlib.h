/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:27:02 by jbergfel          #+#    #+#             */
/*   Updated: 2025/01/05 21:28:01 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHLIB_H
# define MATHLIB_H

# include <math.h>

# define PI 3.1415

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_matrix
{
	double m[4][4];
} t_matrix;

t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_matrix	matrix_rotate_x(double degree);
t_matrix	matrix_rotate_y(double degree);
t_matrix	matrix_rotate_z(double degree);
double		radian(double degree);


t_vector	copy_vector(double x, double y, double z);
t_vector	reverse_vector(t_vector v);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_multiply(t_vector a, t_vector b);
t_vector	vector_double_add(t_vector a, double d);
t_vector	vector_scalar_multiply(t_vector a, double scalar);
t_vector	vector_cross(t_vector a, t_vector b);
t_vector	vector_normalize(t_vector v);
double		vector_len(t_vector a);
double		vector_dot(t_vector a, t_vector b);


#endif
