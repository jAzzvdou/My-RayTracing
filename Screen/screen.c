/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:19:09 by jazevedo          #+#    #+#             */
/*   Updated: 2025/03/24 19:54:16 by jazevedo         ###   ########.fr       */
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

t_texture       load_texture(void *mlx, char *path)
{
        t_texture       texture;

        texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	path = memcard(path, STRING, FREE, 0);
        if (!texture.img)
        {
                err(NULL, "Error\nTexture not found", NULL);
                exit(1);
        }
        texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.linelen, &texture.endian);
        return (texture);
}

void    set_textures(t_world *w, void *mlx)
{
	t_object	*tmp;

	tmp = w->object;
	while (tmp)
	{
		if (tmp->material.pattern.type == TEXTURE)
			w->object->material.pattern.texture = load_texture(mlx, tmp->material.pattern.texture_path);
		tmp = tmp->next;
	}
}

void	screen(t_world *w)
{
	t_minilibx	libx;
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, WIDTH, HEIGHT, "| MiniRT |");
	libx.img = mlx_new_image(libx.mlx, WIDTH, HEIGHT);
	libx.addr = mlx_get_data_addr(libx.img, &libx.bpp, &libx.linelen, &libx.endian);
	set_textures(w, libx.mlx);
	make_the_scene(&libx, w);
	mlx_put_image_to_window(libx.mlx, libx.win, libx.img, 0, 0);
	mlx_hook(libx.win, 2, 1L << 0, key_hook, &libx);
	mlx_hook(libx.win, 17, 0, end_program, &libx);
	mlx_loop(libx.mlx);
	memcard(NULL, 0, FREEALL, 0);
}
