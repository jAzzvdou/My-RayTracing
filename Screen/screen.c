/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:19:09 by jazevedo          #+#    #+#             */
/*   Updated: 2025/02/05 00:47:27 by jazevedo         ###   ########.fr       */
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

void	screen(void)
{
	t_minilibx	libx;

	//libx.map = map;
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, WIDTH, HEIGHT, "| MiniRT |");
	libx.img = mlx_new_image(libx.mlx, WIDTH, HEIGHT);
	libx.addr = mlx_get_data_addr(libx.img, &libx.bpp, &libx.linelen, &libx.endian);
	render_tests(&libx);
	mlx_put_image_to_window(libx.mlx, libx.win, libx.img, 0, 0);
	mlx_hook(libx.win, 2, 1L << 0, key_hook, &libx);
	mlx_hook(libx.win, 17, 0, end_program, &libx);
	mlx_loop(libx.mlx);
}
