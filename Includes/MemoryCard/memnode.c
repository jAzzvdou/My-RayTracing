/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:57:15 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/10 10:18:09 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memorycard.h"

t_memnode	*create_memnode(void *addr)
{
	t_memnode	*new_node;

	new_node = (t_memnode *)malloc(sizeof(t_memnode));
	if (!new_node)
		return (NULL);
	new_node->addr = addr;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_memnode(t_memlist *list, void *addr)
{
	t_memnode	*new_node;

	new_node = create_memnode(addr);
	if (!new_node)
		return ;
	if (!list->first)
	{
		list->first = new_node;
		list->last = new_node;
	}
	else
	{
		list->last->next = new_node;
		new_node->prev = list->last;
		list->last = new_node;
	}
	list->size++;
}

void	remove_memnode(t_memlist *list, t_memnode *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (list->first == node)
		list->first = node->next;
	if (list->last == node)
		list->last = node->prev;
	list->size--;
	clear((void **)&node->addr);
	clear((void **)&node);
}

void	search_memnode(void *content)
{
	t_memnode	*node;
	t_memlist	*list;

	list = memlist_holder(NULL, 0);
	if (!list)
		return ;
	node = list->first;
	while (node)
	{
		if (node->addr == content)
		{
			remove_memnode(list, node);
			return ;
		}
		node = node->next;
	}
}

void	status_memnode(void *addr)
{
	size_t		pos;
	t_memnode	*node;
	t_memlist	*list;

	list = memlist_holder(NULL, 0);
	if (!list)
		return ;
	pos = 0;
	node = list->first;
	while (node)
	{
		if (node->addr == addr)
		{
			printf(GREEN"Está mallocado!\n");
			printf("Posição: %zu | Addr: %p.\n"RESET, pos, node->addr);
			return ;
		}
		node = node->next;
		pos++;
	}
	printf(RED"Não está mallocado ou já foi liberado.\n");
	printf("Addr: %p.\n"RESET, addr);
}
