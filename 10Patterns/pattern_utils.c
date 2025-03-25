/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:43:15 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:44:09 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_color	sphere_texture(t_pattern p, t_point pt)
{
	t_uv	uv;
	double	phi;
	double	theta;

	theta = atan2(pt.x, pt.z);
	phi = acos(pt.y);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = 1 - (phi / M_PI);
	return (texture_color(p.texture, uv));
}

t_color	plane_texture(t_pattern p, t_point pt)
{
	t_uv	uv;

	uv.u = fmod(pt.x, 1);
	uv.v = fmod(pt.z, 1);
	return (texture_color(p.texture, uv));
}

t_color	cylinder_texture(t_pattern p, t_point pt)
{
	t_uv	uv;
	double	theta;

	theta = atan2(pt.x, pt.z);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = fmod(pt.y, 1);
	return (texture_color(p.texture, uv));
}

t_color	cone_texture(t_pattern p, t_point pt)
{
	t_uv	uv;
	double	theta;
	double	radius;

	radius = pow(pt.x, 2) + pow(pt.z, 2);
	theta = atan2(pt.x, pt.z);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = fmod(sqrt(radius), 1);
	return (texture_color(p.texture, uv));
}

t_color	texture_at(t_pattern p, t_object obj, t_point pt)
{
	if (obj.type == SP)
		return (sphere_texture(p, pt));
	if (obj.type == PL)
		return (plane_texture(p, pt));
	if (obj.type == CY)
		return (cylinder_texture(p, pt));
	if (obj.type == CN)
		return (cone_texture(p, pt));
	return (color(0, 0, 0));
}
