/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_for_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:29:54 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:30:00 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_ray	ray_for_pixel(t_camera c, int px, int py)
{
	double		d[4];
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	d[0] = (px + 0.5) * c.pixel_size;
	d[1] = (py + 0.5) * c.pixel_size;
	d[2] = c.half_width - d[0];
	d[3] = c.half_height - d[1];
	pixel = mult_matrix_tuple(c.inverse, point(d[2], d[3], -1));
	origin = mult_matrix_tuple(c.inverse, point(0, 0, 0));
	direction = normalize(sub_tuple(pixel, origin));
	return (ray(origin, direction));
}
