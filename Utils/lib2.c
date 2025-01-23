/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:52:20 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/22 21:48:38 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

char	*my_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*new_s;

	if (!s1 && !s2)
		return (NULL);
	new_s = memcard(NULL, STRING, MALLOC, my_strlen(s1) + my_strlen(s2));
	i = 0;
	while (s1 && *s1)
		new_s[i++] = *s1++;
	while (s2 && *s2)
		new_s[i++] = *s2++;
	new_s[i] = '\0';
	return (new_s);
}

char	*my_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_size;
	char	*new_s;

	s_size = my_strlen(s);
	if ((size_t)start > s_size)
		return (memcard("", STRING, MALLOC, my_strlen("")));
	s += start;
	s_size -= start;
	if (s_size > len)
		s_size = len;
	new_s = memcard(NULL, STRING, MALLOC, s_size);
	i = -1;
	while (++i < s_size)
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

void	my_bzero(void *s, size_t n)
{
	char	*zero_s;

	zero_s = s;
	while (n--)
		zero_s[n] = 0;
}
