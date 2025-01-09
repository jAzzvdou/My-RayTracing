/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:52:28 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/26 12:45:55 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_rgb(char *line)
{
	int		rgb[3];
	char	**split;

	split = splitline(line, ',');
	if (matrixlen(split) != 3)
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	if (!onlynumber(split[0], INT) || !onlynumber(split[1], INT)
		|| !onlynumber(split[2], INT))
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	rgb[0] = my_atoi(split[0]);
	rgb[1] = my_atoi(split[1]);
	rgb[2] = my_atoi(split[2]);
	split = memcard(split, VECTOR, FREE, 0);
	if (rgb[0] > 255 || rgb[0] < 0
		|| rgb[1] > 255 || rgb[1] < 0
		|| rgb[2] > 255 || rgb[2] < 0)
		return (1);
	return (0);
}

int	invalid_coord(char *line)
{
	char	**split;

	split = splitline(line, ',');
	if (matrixlen(split) != 3)
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	if (!onlynumber(split[0], DOUBLE) || !onlynumber(split[1], DOUBLE)
		|| !onlynumber(split[2], DOUBLE))
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	return (split = memcard(split, VECTOR, FREE, 0), 0);
}

int	invalid_vector(char *line)
{
	int		xyz[3];
	char	**split;

	split = splitline(line, ',');
	if (matrixlen(split) != 3)
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	if (!onlynumber(split[0], DOUBLE) || !onlynumber(split[1], DOUBLE)
		|| !onlynumber(split[2], DOUBLE))
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	xyz[0] = my_atod(split[0]);
	xyz[1] = my_atod(split[1]);
	xyz[2] = my_atod(split[2]);
	if (xyz[0] < -1 || xyz[0] > 1
		|| xyz[1] < -1 || xyz[1] > 1
		|| xyz[2] < -1 || xyz[2] > 1)
		return (split = memcard(split, VECTOR, FREE, 0), 1);
	return (split = memcard(split, VECTOR, FREE, 0), 0);
}
