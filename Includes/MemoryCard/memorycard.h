/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorycard.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:42:49 by jazevedo          #+#    #+#             */
/*   Updated: 2025/03/27 08:52:51 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORYCARD_H
# define MEMORYCARD_H

# include <stdlib.h> //| MALLOC, FREE, NULL
# include <stdio.h>  //| PRINTF

//----------| DEFINES |----------//
# define FREEALL -1
# define FREE    1
# define MALLOC  2
# define STATUS  3
# define PRINT   4

# define DEFAULT 5
# define STRING  6
# define VECTOR  7
# define INTS    8

# define RED     "\001\033[38;2;255;0;0m\002"
# define GREEN   "\001\033[38;2;0;255;0m\002"
# define YELLOW  "\001\033[38;2;255;255;0m\002"
# define ORANGE	 "\001\033[38;2;255;165;0m\002"
# define WHITE   "\001\033[38;2;255;255;255m\002"
# define RESET   "\033[0m"

//----------| STRUCTS |----------//
typedef struct s_memnode
{
	void				*addr;
	struct s_memnode	*next;
	struct s_memnode	*prev;
}	t_memnode;

typedef struct s_memlist
{
	t_memnode	*first;
	t_memnode	*last;
	size_t		size;
}	t_memlist;

//----------| MEMORYCARD |----------//
void		*memcard(void *content, int type, int mallocfree, size_t memsize);

//----------| MEMLIST |----------//
t_memlist	*start_memlist(void);
t_memnode	*create_memnode(void *addr);
void		add_memnode(t_memlist *list, void *addr);
void		remove_memnode(t_memlist *list, t_memnode *node);
void		search_memnode(void *content);
void		status_memnode(void *addr);
t_memlist	*memlist_holder(t_memlist *new_list, int tofree);
void		print_memlist(void);

//----------| TYPES FUNCTIONS |----------//
void		*type_default(void *ptr, int tofree, size_t memsize);
char		*type_str(char *s, int tofree, size_t memsize);
char		**type_vector(char **vector, int tofree, size_t memsize);
int			*type_ints(int *arr, int tofree, size_t memsize);

//----------| TYPES FUNCTIONS UTILS |----------//
char		**fillvector(char **vector, size_t memsize);

//----------| CLEANERS |----------//
void		clear(void **content);
void		clear_vector(char **vector);
void		clear_memlist(void);

//----------| UTILS |----------//
size_t		strsize(const char *s);
void		fillzero(void *s, size_t n);

#endif //| MEMORYCARD
