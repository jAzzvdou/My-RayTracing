/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 15:52:57 by jbergfel          #+#    #+#             */
/*   Updated: 2025-01-08 15:52:57 by jbergfel         ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"

t_vector	copy_vector(double x, double y, double z)
{
	t_vector result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vector	reverse_vector(t_vector v)
{
	return (copy_vector(-v.x, -v.y, -v.z));
}

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	result;

	result = copy_vector(a.x + b.x, a.y + b.y, a.z + b.z);
	return (result);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result = copy_vector(a.x - b.x, a.y - b.y, a.z - b.z);
	return (result);
}

t_vector	vector_multiply(t_vector a, t_vector b)
{
	t_vector	result;

	result = copy_vector(a.x * b.x, a.y * b.y, a.z * b.z);
	return (result);
}

t_vector	vector_double_add(t_vector a, double d)
{
	t_vector	result;

	result = copy_vector(a.x + d, a.y + d, a.z + d);
	return (result);
}

t_vector	vector_scalar_multiply(t_vector a, double scalar)
{
	t_vector	result;

	result = copy_vector(a.x * scalar, a.y * scalar, a.z * scalar);
	return (result);
}

double	vector_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vector_normalize(t_vector v)
{
	double	len;
	double	inv_len;

	len = vector_len(v);
	if (len > 1e-6)
	{
		inv_len = 1.0 / len;
		v.x *= inv_len;
		v.y *= inv_len;
		v.z *= inv_len;
	}
	return (v);
}

double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.y);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	double	x;
	double	y;
	double	z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return (copy_vector(x, y, z));
}
