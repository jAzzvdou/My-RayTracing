/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:19:09 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/18 14:14:58 by jbergfel         ###   ########.fr       */
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

void	screen(t_minilibx *libx)
{
	libx->mlx = mlx_init();
	libx->win = mlx_new_window(libx->mlx, WIDTH, HEIGHT, "| MiniRT |");
	libx->img = mlx_new_image(libx->mlx,  WIDTH, HEIGHT);
	libx->addr = mlx_get_data_addr(libx->img, &libx->bpp, \
			&libx->linelen, &libx->endian);
	//| Aqui vamos desenhar na imagem.
	make_sphere(libx, 640, 360, 100);
	mlx_put_image_to_window(libx->mlx, libx->win, libx->img, 0, 0);
	//| Aqui dá pra colocar um menu na tela se a gente quiser.
	mlx_hook(libx->win, KEY_EVENT, 1L << 0, key_hook, libx);
	mlx_hook(libx->win, DESTROY, 1L << 2, end_program, libx);
	mlx_loop(libx->mlx);
}
