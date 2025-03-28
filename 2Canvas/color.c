/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:07:21 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:49:37 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_color	color(double r, double g, double b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	add_color(t_color a, t_color b)
{
	return (color(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color	sub_color(t_color a, t_color b)
{
	return (color(a.r - b.r, a.g - b.g, a.b - b.b));
}

t_color	mult_color(t_color a, double b)
{
	return (color(a.r * b, a.g * b, a.b * b));
}

t_color	hadama_color(t_color a, t_color b)
{
	return (color((a.r * b.r), (a.g * b.g), (a.b * b.b)));
}
