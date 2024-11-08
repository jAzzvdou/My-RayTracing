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

t_vector	vector_scalar(t_vector a, double scalar)
{
	t_vector result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

t_vector	vector_len(t_vector a)
{
	t_vector result;

	result.x = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	result.y = 0;
	result.z = 0;
	return (result);
}
