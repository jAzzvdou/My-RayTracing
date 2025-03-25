/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:04 by jazevedo          #+#    #+#             */
/*   Updated: 2025/03/25 15:47:48 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minirt.h"

void	err(char *color1, char *error, char *color2)
{
	if (color1)
		write(2, color1, my_strlen(color1));
	if (error)
		write(2, error, my_strlen(error));
	if (color2)
		write(2, color2, my_strlen(color2));
}

int	invalid_arguments(int ac, char **av)
{
	if (ac != 2)
		return (err(RED, ARGV, RESET), 1);
	if (revstrncmp(".rt", av[1], 4))
		return (err(RED, FILENAME, RESET), 1);
	return (0);
}

void	start_libx(t_minilibx *libx)
{
	libx->mlx = mlx_init();
	libx->win = mlx_new_window(libx->mlx, WIDTH, HEIGHT, "| MiniRT |");
	libx->img = mlx_new_image(libx->mlx, WIDTH, HEIGHT);
	libx->addr = mlx_get_data_addr(libx->img, &libx->bpp,
			&libx->linelen, &libx->endian);
}

int	main(int ac, char **av)
{
	int			fd;
	t_world		w;
	t_minilibx	libx;

	if (invalid_arguments(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (err(RED, av[1], RESET), 2);
	memlist_holder(start_memlist(), 0);
	start_libx(&libx);
	w = world();
	if (!parse(&w, fd, libx.mlx))
		return (memcard(NULL, 0, FREEALL, 0), 3);
	screen(&w, libx);
	return (0);
}
