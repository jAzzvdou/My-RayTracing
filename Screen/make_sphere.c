/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:16:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/09/18 14:22:39 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

void draw_horizontal_line(t_minilibx *libx, int x_start, int x_end, int y, int color)
{
	if (y < 0 || y >= HEIGHT)
		return;
	if (x_start < 0)
		x_start = 0;
	if (x_end >= WIDTH)
		x_end = WIDTH - 1;

	for (int x = x_start; x <= x_end; x++)
		draw_pixel(libx, x, y, color);
}

void	make_sphere(t_minilibx *libx, int x_center, int y_center, int radius) // still a circle
{
	int	x = 0;
	int	y = radius; // radius
	int	d = 1 - radius;
	int	deltaE = 3;
	int	deltaSE = -2 * radius + 5;

	while (y >= x)
	{
		draw_horizontal_line(libx, x_center - x, x_center + x, y_center + y, 0xFFFFFF);
		draw_horizontal_line(libx, x_center - x, x_center + x, y_center - y, 0xFFFFFF);
		draw_horizontal_line(libx, x_center - y, x_center + y, y_center + x, 0xFFFFFF);
		draw_horizontal_line(libx, x_center - y, x_center + y, y_center - x, 0xFFFFFF);
		if (d < 0)
		{
			d += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else
		{
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
	}
}
