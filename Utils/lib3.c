/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:03:28 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/17 10:15:26 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

size_t	matrixlen(char **matrix)
{
	size_t	i;

	if (!matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	mult;

	nb = 0;
	mult = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		mult = -mult;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb * mult);
}

double	ft_atod(const char *nptr)
{
	double	nb;
	int	mult;

	nb = 0;
	mult = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		mult = -mult;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb * mult);
}
