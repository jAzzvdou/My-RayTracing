/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:22:37 by jbergfel          #+#    #+#             */
/*   Updated: 2024/11/07 22:43:27 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/mathlib.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	t_vector result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector	vector_multiply(t_vector a, t_vector b)
{
	t_vector result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

t_vector	vector_scalar_multiply(t_vector a, double scalar)
{
	t_vector result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

double	vector_len(t_vector v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector	vector_normalize(t_vector v)
{
	double	w;
	t_vector result;

	w = vector_len(v);
	result.x = v.x / w;
	result.y = v.y / w;
	result.z = v.z / w;
	return (result);
}

double	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.y);
}

t_vector vector_cross(t_vector a, t_vector b)
{
	t_vector result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
