/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:07:17 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/18 01:08:33 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_canvas	create_canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.pixel = (t_color *)memcard(NULL, DEFAULT, MALLOC, sizeof(t_color) * width * height);
	my_bzero(canvas.pixel, sizeof(t_color *) * width * height);
	if (!canvas.pixel)
	{
		canvas.pixel = memcard(canvas.pixel, DEFAULT, FREE, 0);
		exit(1);
	}
	return (canvas);
}

void	draw_pixel(t_minilibx *libx, int x, int y, int color)
{
	char	*pixel;

	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;
	pixel = libx->addr + (y * libx->linelen + x * (libx->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	set_canvas_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	if (y >= canvas->height || x >= canvas->width || x < 0 || y < 0)
		return ;
	canvas->pixel[y * canvas->width + x] = color;
}

t_color	pixel_at(t_canvas *canvas, int x, int y)
{
	if (y >= canvas->height || x >= canvas->width || x < 0 || y < 0)
		return ((t_color){0, 0, 0});
	return (canvas->pixel[y * canvas->width + x]);
}

void	draw_canvas(t_minilibx *libx, t_canvas *canvas)
{
	int	x;
	int	y;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			draw_pixel(libx, x, y, color_to_int(pixel_at(canvas, x, y)));
			x++;
		}
		y++;
	}
}
