/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:14:26 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 13:57:05 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_int(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_double(char *s)
{
	int	i;
	int	dot;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	dot = 0;
	while (s[i])
	{
		if (s[i] == '.')
			dot++;
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (dot > 1)
		return (0);
	return (1);
}

int	onlynumber(char *s, int type)
{
	if (!s)
		return (0);
	if (type == INT)
		return (is_int(s));
	if (type == DOUBLE)
		return (is_double(s));
	return (0);
}
