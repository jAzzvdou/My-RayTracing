/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:04 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/22 21:57:33 by jazevedo         ###   ########.fr       */
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

int	invalid_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (err(RED, ARGV, RESET), 1);
	if (revstrncmp(".rt", argv[1], 4))
		return (err(RED, FILENAME, RESET), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argv;
	if (invalid_arguments(argc, argv))
		return (-1);
	memlist_holder(start_memlist(), 0);
	//NOSSO PARSER NO FUTURO
	screen(map);

	memcard(NULL, 0, FREEALL, 0); //POR SEGURANÇA, UM GARBADE COLLECTOR
	return (0);
}
