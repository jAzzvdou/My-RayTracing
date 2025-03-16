/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:50:06 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/16 12:06:56 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_matrix	rotationx(double rad)
{
	t_matrix	m;

	m = identity();
	set_index(&m, 1, 1, cos(rad));
	set_index(&m, 2, 1, -sin(rad));
	set_index(&m, 1, 2, sin(rad));
	set_index(&m, 2, 2, cos(rad));
	return (m);
}

t_matrix	rotationy(double rad)
{
	t_matrix	m;

	m = identity();
	set_index(&m, 0, 0, cos(rad));
	set_index(&m, 2, 0, sin(rad));
	set_index(&m, 0, 2, -sin(rad));
	set_index(&m, 2, 2, cos(rad));
	return (m);
}

t_matrix	rotationz(double rad)
{
	t_matrix	m;

	m = identity();
	set_index(&m, 0, 0, cos(rad));
	set_index(&m, 1, 0, -sin(rad));
	set_index(&m, 0, 1, sin(rad));
	set_index(&m, 1, 1, cos(rad));
	return (m);
}
