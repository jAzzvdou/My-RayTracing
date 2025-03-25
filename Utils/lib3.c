/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:03:28 by jazevedo          #+#    #+#             */
/*   Updated: 2025/03/25 13:28:56 by jbergfel         ###   ########.fr       */
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

int	my_atoi(const char *nptr)
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

int	power(int base, int exp)
{
	int	result;

	result = 1;
	while (exp)
	{
		result *= base;
		exp--;
	}
	return (result);
}

double	parse_fractional_part(const char *nptr, double nb, int *i)
{
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb + ((double)(*nptr - '0') / power(10, *i + 1));
		nptr++;
		(*i)++;
	}
	return (nb);
}

double	my_atod(const char *nptr)
{
	int		i;
	double	nb;
	double	mult;

	nb = 0;
	mult = 1;
	i = 0;
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
	if (*nptr == '.')
	{
		nptr++;
		nb = parse_fractional_part(nptr, nb, &i);
	}
	return (nb * mult);
}
