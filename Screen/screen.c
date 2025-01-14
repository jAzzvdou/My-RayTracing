/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:19:09 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/14 06:16:19 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	end_program(t_minilibx *libx)
{
	mlx_destroy_image(libx->mlx, libx->img);
	mlx_destroy_window(libx->mlx, libx->win);
	mlx_destroy_display(libx->mlx);
	free(libx->mlx);
	memcard(NULL, 0, FREEALL, 0);
	exit(0);
	return (0);
}

int	key_hook(int key, t_minilibx *libx)
{
	if (key == ESC)
		end_program(libx);
	return (0);
}

void	draw_pixel(t_minilibx *libx, int x, int y, int color)
{
	char	*pixel;

	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;
	pixel = libx->addr + (y * libx->linelen + x * (libx->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	screen(t_main *main)
{
	main->libx->mlx = mlx_init();
	main->libx->win = mlx_new_window(main->libx->mlx, WIDTH, HEIGHT, "| MiniRT |");
	main->libx->img = mlx_new_image(main->libx->mlx, WIDTH, HEIGHT);
	main->libx->addr = mlx_get_data_addr(main->libx->img, &main->libx->bpp, \
			&main->libx->linelen, &main->libx->endian);
	//| Aqui vamos desenhar na imagem.
	//make_sphere(main, 640, 360, main->map->sp->diameter);
	render_graphics(main);
	//| Aqui dá pra colocar um menu na tela se a gente quiser.
	mlx_key_hook(main->libx->mlx, &key_hook, &main->libx);
	mlx_loop(main->libx->mlx);
}

static t_vector	start_ray(t_cam *cam, int x, int y)
{
	double		norm_x;
	double		norm_y;
	t_vector	cam_ray;
	//t_vector	world_ray;

	norm_x = ((2.0 * (x + 0.5) / WIDTH) - 1.0) * cam->aspect_ratio * cam->scale;
	norm_y = (1.0 - (2.0 * (y + 0.5) / HEIGHT)) * cam->scale;

	cam_ray = copy_vector(norm_x, norm_y, 1.0);
	//world_ray =

	return (cam_ray);
}

static void	render_pixels(t_main *main, int x, int y)
{
	t_vector	rays;
	//int			pixel_rgb;

	rays = start_ray(main->map->c, x, y);

	(void) rays;
}

void	render_graphics(t_main *main)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixels(main, x, y);
			x++;
		}
		y++;
	}
}
