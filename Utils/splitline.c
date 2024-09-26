/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:06:58 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/18 11:47:08 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

static size_t	countwords1(char const *s, char c)
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

char	**split_with_c(char const *s, char c)
{
	size_t	i;
	size_t	words;
	size_t	wordsize;
	char	**final;

	words = countwords1(s, c);
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

static size_t	countwords2(char const *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		if (!is_space(*s))
			length++;
		while (*s && !is_space(*s))
			s++;
		while (*s && is_space(*s))
			s++;
	}
	return (length);
}

char	**split_without_c(char const *s)
{
	size_t	i;
	size_t	words;
	size_t	wordsize;
	char	**final;

	words = countwords2(s);
	final = memcard(NULL, VECTOR, MALLOC, words);
	if (!final)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (is_space(*s))
			s++;
		wordsize = 0;
		while (s[wordsize] && !is_space(s[wordsize]))
			wordsize++;
		final[i] = ft_substr(s, 0, wordsize);
		if (!final[i])
			return (final = memcard(final, VECTOR, FREE, 0), NULL);
		s += wordsize;
	}
	return (final[i] = NULL, final);
}

char	**splitline(char const *s, char c)
{
	if (!s)
		return (NULL);
	if (!c)
		return (split_without_c(s));
	return (split_with_c(s, c));
}
