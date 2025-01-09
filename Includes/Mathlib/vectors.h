/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:53:45 by jbergfel          #+#    #+#             */
/*   Updated: 2025/01/09 11:46:33 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	copy_vector(double x, double y, double z);
t_vector	reverse_vector(t_vector v);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_multiply(t_vector a, t_vector b);
t_vector	vector_double_add(t_vector a, double d);
t_vector	vector_scalar_multiply(t_vector a, double scalar);
t_vector	vector_normalize(t_vector v);
double		vector_len(t_vector a);
double		vector_dot(t_vector a, t_vector b);

#endif
