/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:41:29 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/19 23:36:28 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] != c)
		{
			i++;
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
	return (i);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**the_split(const char *s, char c, char **arr)
{
	size_t	wordl;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			wordl = word_len(s + i, c);
			arr[j] = memcard(NULL, STRING, MALLOC, sizeof(char) * (wordl + 1));
			if (!arr[j])
				arr = memcard(arr, VECTOR, FREE, 0);
			k = 0;
			while (k < wordl)
				arr[j][k++] = s[i++];
			arr[j++][wordl] = '\0';
		}
	}
	arr[j] = NULL;
	return (arr);
}

char	**my_split(const char *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = memcard(NULL, VECTOR, MALLOC, sizeof(*arr) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	the_split(s, c, arr);
	return (arr);
}
