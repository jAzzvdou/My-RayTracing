/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:56:22 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/11 10:05:33 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memorycard.h"

t_memlist	*start_memlist(void)
{
	t_memlist	*list;

	list = malloc(sizeof(t_memlist));
	if (!list)
		return (NULL);
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	return (list);
}

t_memlist	*memlist_holder(t_memlist *new_list, int tofree)
{
	static t_memlist	*list;

	if (new_list)
	{
		if (list)
			clear_memlist();
		list = new_list;
	}
	if (tofree && list)
		clear_memlist();
	return (list);
}

void	print_memlist(void)
{
	t_memnode	*node;
	t_memlist	*list;
	size_t		pos;

	list = memlist_holder(NULL, 0);
	if (!list)
	{
		printf(GREEN"Lista vazia\n"RESET);
		return ;
	}
	node = list->first;
	pos = 0;
	while (node)
	{
		printf(WHITE"Posição: %zu, Endereço: %p\n"RESET, pos, node->addr);
		node = node->next;
		pos++;
	}
}
