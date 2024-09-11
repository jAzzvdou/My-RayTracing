/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorycard_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:52:55 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/11 09:12:17 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memorycard.h"

size_t	strsize(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	fillzero(void *s, size_t n)
{
	char	*zero;

	zero = s;
	while (n--)
		zero[n] = 0;
}
