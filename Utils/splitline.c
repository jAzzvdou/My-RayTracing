/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:06:58 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/15 11:13:34 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_size;
	char	*new_s;

	s_size = ft_strlen(s);
	if ((size_t)start > s_size)
		return (memcard("", STRING, MALLOC, ft_strlen(""));
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

static size_t	countwords(char const *s, char c)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		if (*s != c)
			length++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (length);
}

char	**splitline(char const *s, char c)
{
	size_t	i;
	size_t	words;
	size_t	wordsize;
	char	**final;

	if (!s)
		return (NULL);
	words = countwords(s, c);
	final = memcard(NULL, VECTOR, MALLOC, words);
	if (!final)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		wordsize = 0;
		while (s[wordsize] && s[wordsize] != c)
			wordsize++;
		final[i] = ft_substr(s, 0, wordsize);
		if (!final[i])
			return (final = memcard(final, VECTOR, FREE, 0), NULL);
		s += wordsize;
	}
	return (final[i] = NULL, final);
}
