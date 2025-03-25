/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:03:24 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:51:26 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

static void	get_angles(t_vector v, double *x, double *z)
{
	*x = 0;
	*z = 0;
	if (fabs(v.y) == 1)
		return ;
	else if (!near_zero(v.z))
		*x = atan2(v.z, sqrt(v.x * v.x + v.y * v.y));
	else if (!near_zero(v.x))
		*z = atan2(v.x, sqrt(v.y * v.y + v.z * v.z));
}

t_matrix	rot_m(double x, double z)
{
	return (mult_matrix(rotationx(x), rotationz(z)));
}

t_matrix	get_matrix(t_matrix scale, t_matrix rotate, t_matrix translate)
{
	return (mult_matrix(mult_matrix(scale, rotate), translate));
}

t_matrix	rotate_matrix(t_point p, t_vector d, t_object obj)
{
	double	r;
	double	x;
	double	z;

	x = 0;
	z = 0;
	r = 1;
	get_angles(d, &x, &z);
	if (obj.type == SP || obj.type == CY || obj.type == CN)
		r = obj.radius;
	return (get_matrix(translation(p.x, p.y, p.z),
			rot_m(x, z), scaling(r, r, r)));
}
