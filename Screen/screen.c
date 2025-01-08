/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:19:09 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/07 11:33:30 by jbergfel         ###   ########.fr       */
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
	make_sphere(main, 640, 360, main->map->sp->diameter);
	mlx_put_image_to_window(main->libx->mlx, main->libx->win, main->libx->img, 0, 0);
	//| Aqui dá pra colocar um menu na tela se a gente quiser.
	mlx_loop_hook(main->libx->mlx, &main_gr_loop, &main);
	mlx_loop(main->libx->mlx);
}

void	main_gr_loop(void *data)
{
	t_main	*main_graph;

	main_graph = data;
	//func para key hook
	render_graphics(main_graph);
}

void	render_graphics(t_main *main_graph)
{
	t_map	*map;

	map = main_graph->map;
}
