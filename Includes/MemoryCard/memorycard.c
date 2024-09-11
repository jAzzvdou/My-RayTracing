/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorycard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:02:40 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/11 09:15:19 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memorycard.h"

void	*memcard(void *content, int type, int mallocfree, size_t memsize)
{
	if (mallocfree == FREEALL)
		return (memlist_holder(NULL, FREE), NULL);
	else if (type == DEFAULT)
		return (type_default(content, mallocfree, memsize));
	else if (type == STRING)
		return (type_str((char *)content, mallocfree, memsize));
	else if (type == VECTOR)
		return (type_vector((char **)content, mallocfree, memsize));
	else if (type == INTS)
		return (type_ints((int *)content, mallocfree, memsize));
	else if (type == STATUS)
		return (status_memnode(content), NULL);
	else if (type == PRINT)
		return (print_memlist(), NULL);
	return (NULL);
}
