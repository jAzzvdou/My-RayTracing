/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:29:46 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:29:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_matrix	get_orientation(t_vector v[3])
{
	t_matrix	orientation;

	orientation = identity();
	set_index(&orientation, 0, 0, v[1].x);
	set_index(&orientation, 1, 0, v[1].y);
	set_index(&orientation, 2, 0, v[1].z);
	set_index(&orientation, 0, 1, v[2].x);
	set_index(&orientation, 1, 1, v[2].y);
	set_index(&orientation, 2, 1, v[2].z);
	set_index(&orientation, 0, 2, -v[0].x);
	set_index(&orientation, 1, 2, -v[0].y);
	set_index(&orientation, 2, 2, -v[0].z);
	return (orientation);
}

t_matrix	view_transform(t_point from, t_point to, t_vector up)
{
	t_vector	v[3];

	v[0] = normalize(sub_tuple(to, from));
	if (1 - fabs(dot(v[0], up)) < EPSILON)
		v[1] = vector(-1, 0, 0);
	else
		v[1] = cross(v[0], normalize(up));
	v[2] = cross(v[1], v[0]);
	return (mult_matrix(get_orientation(v),
				translation(-from.x, -from.y, -from.z)));
}

t_camera	camera(int hsize, int vsize, double fov)
{
	double		half_view;
	double		aspect;
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = fov;
	c.transform = identity();
	half_view = tan(fov / 2);
	aspect = (double)hsize / (double)vsize;
	c.half_width = half_view;
	c.half_height = half_view;
	if (aspect >= 1)
		c.half_height = half_view / aspect;
	else
		c.half_width = half_view * aspect;
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}
