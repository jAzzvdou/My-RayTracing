/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:56:03 by jbergfel          #+#    #+#             */
/*   Updated: 2025/01/09 11:46:10 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <math.h>

# define PI 3.1415

typedef struct s_matrix
{
	double m[4][4];
} t_matrix;

t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_matrix	matrix_rotate_x(double degree);
t_matrix	matrix_rotate_y(double degree);
t_matrix	matrix_rotate_z(double degree);
double		radian(double degree);


#endif
