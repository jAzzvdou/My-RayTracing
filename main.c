/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:04 by jazevedo          #+#    #+#             */
/*   Updated: 2025/03/18 00:53:53 by jazevedo         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_world w;
	int fd;

	if (invalid_arguments(ac, av))
		return (-1);
	memlist_holder(start_memlist(), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		perror(av[1]);
	//w = world();
	if (fd < 0 || !parse(fd, &w))
		printf("invalid map!");
	//screen(&w);
	memcard(NULL, 0, FREEALL, 0); //POR SEGURANÇA, UM GARBADE COLLECTOR
	return (0);
}
