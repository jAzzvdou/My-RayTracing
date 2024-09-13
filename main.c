/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:04 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/13 18:11:20 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	end_program(t_minilibx *libx)
{
	mlx_destroy_image(libx->mlx, libx->img);
	mlx_destroy_window(libx->mlx, libx->win);
	mlx_destroy_display(libx->mlx);
	free(libx->mlx);
	exit(0);
	return (0);
}

int	key_hook(int key, t_minilibx *libx)
{
	if (key == ESC)
		end_program(libx);
	return (0);
}

void	test(t_minilibx *libx)
{
	libx->mlx = mlx_init();
	libx->win = mlx_new_window(libx->mlx, WIDTH, HEIGHT, "| MiniRT |");
	libx->img = mlx_new_image(libx->mlx,  WIDTH, HEIGHT);
	libx->addr = mlx_get_data_addr(libx->img, &libx->bpp, \
			&libx->linelen, &libx->endian);
	mlx_put_image_to_window(libx->mlx, libx->win, libx->img, 0, 0);
	//| Aqui dá pra colocar um menu na tela se a gente quiser.
	mlx_hook(libx->win, KEY_EVENT, 1L << 0, key_hook, libx);
	mlx_hook(libx->win, DESTROY, 1L << 2, end_program, libx);
	mlx_loop(libx->mlx);
}

int	invalid_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (revstrncmp(".rt", argv[1], 4))
		return (1);
	return (0);
}

t_map	*start_map(void)
{
	t_map	*map;

	map = memcard(NULL, DEFAULT, MALLOC, sizeof(t_map));
	if (!map)
		return (NULL);
	map->a = NULL;
	map->c = NULL;
	map->l = NULL;
	map->pl = NULL;
	map->sp = NULL;
	map->cy = NULL;
	return (map);
}

t_map	*readmap(char *file)
{
	int	fd;
	char	*line;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = start_map();
	line = get_next_line(fd);
	while (line)
	{
		//| Adicionar a linha na lista correta.
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (invalid_arguments(argc, argv))
		return (-1); //| Fazer retornar uma mensagem de erro no STDERR.
	memlist_holder(start_memlist(), 0); //| Inicializa o memorycard.
	main = (t_main){0};
	main.map = readmap(argv[1]); //| Aqui a gente tem que pegar as informações do arquivo. (Mini Parsing).
	if (!main.map)
		return (-1); //| Erro. Mapa inválido.
	//| Fazer a MiniRT funcionar.
	test(&libx);
	return (0);
}

//| Fiz apenas um teste abrindo uma imagem e fazendo-a fechar no ESC ou no x.
