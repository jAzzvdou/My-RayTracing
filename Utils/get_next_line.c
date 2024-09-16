/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:51:05 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/16 15:20:35 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

char	*free_function(char *wardrobe, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(wardrobe, buffer);
	wardrobe = memcard(wardrobe, STRING, FREE, 0);
	return (temp);
}

char	*cutter(char *wardrobe)
{
	int		end;
	char	*single;

	end = 0;
	while (wardrobe[end] && wardrobe[end] != '\n')
		end++;
	if (wardrobe[end] == '\n')
		end++;
	single = memcard(NULL, STRING, MALLOC, end);
	single[end] = '\0';
	while (end--)
		single[end] = wardrobe[end];
	if (single[0] == '\0')
		return (single = memcard(single, STRING, FREE, 0), NULL);
	return (single);
}

char	*remover(char *wardrobe)
{
	int		end;
	int	size;
	char	*new_wardrobe;

	end = 0;
	while (wardrobe[end] && wardrobe[end] != '\n')
		end++;
	if (wardrobe[end] == '\n')
		end++;
	if (wardrobe[end] == '\0')
		return (wardrobe = memcard(wardrobe, STRING, FREE, 0), NULL);
	size = ft_strlen(wardrobe + end);
	new_wardrobe = memcard(wardrobe + end, STRING, MALLOC, size);
	wardrobe = memcard(wardrobe, STRING, FREE, 0);
	return (new_wardrobe);
}

char	*reader(int fd)
{
	static char	*wardrobe;
	char		*buffer;
	char		*single;
	int			bytes;

	bytes = 1;
	buffer = memcard(NULL, STRING, MALLOC, BUFFER_SIZE);
	while (bytes > 0 && (!wardrobe || !ft_strchr(wardrobe, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			buffer = memcard(buffer, STRING, FREE, 0);
			return (NULL);
		}
		buffer[bytes] = '\0';
		wardrobe = free_function(wardrobe, buffer);
	}
	buffer = memcard(buffer, STRING, FREE, 0);
	single = cutter(wardrobe);
	wardrobe = remover(wardrobe);
	return (single);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	return (reader(fd));
}
