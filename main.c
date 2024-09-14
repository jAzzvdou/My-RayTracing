/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:04 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/13 21:32:41 by jazevedo         ###   ########.fr       */
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

void	err(char *color1, char *error, char *color1)
{
	if (color1)
		write(2, color1, ft_strlen(color1));
	if (error)
		write(2, error, ft_strlen(error));
	if (color2)
		write(2, color2, ft_strlen(color2));
}

int	invalid_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (err(RED, ARGV, RESET), 1);
	if (revstrncmp(".rt", argv[1], 4))
		return (err(RED, FILENAME, RESET), 1);
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

int	add_map(t_map *map, char *line)
{
	if (line[0] == 'A')
		return (1)
	else if (line[0] == 'C')
		return (1)
	else if (line[0] == 'L')
		return (1)
	else if (!strncmp(line, "PL ", 3))
		return (1)
	else if (!strncmp(line, "SP ", 3))
		return (1)
	else if (!strncmp(line, "CY ", 3))
		return (1)
	err(RED, INVALID_VARIABLE, RESET);
	return (0);
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
		skip_spaces(&line);
		if (line[0] != '\n')
			if (add_map(map, line))
				return (NULL);
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
