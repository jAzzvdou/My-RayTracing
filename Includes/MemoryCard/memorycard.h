/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorycard.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:42:49 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/09 12:47:51 by jazevedo         ###   ########.fr       */
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
	void			*addr;
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
void	*type_default(void *ptr, int tofree, size_t memsize);
char	*type_str(char *s, int tofree, size_t memsize);
char	**type_vector(char **vector, int tofree, size_t memsize);
int	*type_ints(int *arr, int tofree, size_t memsize);

//----------| TYPES FUNCTIONS UTILS |----------//
char	**fillvector(char **vector, size_t memsize);

//----------| CLEANERS |----------//
void		clear(void **content);
void		clear_vector(char **vector);
void		clear_memlist(void);

//----------| UTILS |----------//
size_t		strsize(const char *s);
void		fillzero(void *s, size_t n);

#endif //| MEMORYCARD

/*
A função MEMCARD foi desenvolvida para facilitar a alocação e liberação de memória.

Ela funciona da seguinte forma:
Tem uma struct, que é uma lista duplamente encadeada, que armazena todos os endereços de memória alocados.
Todos os conteúdos alocados são armazenados nessa lista.

Para inicializar essa lista no começo do programa, basta chamar a função 'memlist_holder(start_memlist(), 0)'.
A função memlist_holder é uma função que armazena a lista de memória em uma variável estática, ou seja, ela só será inicializada uma vez e poderá ser acessada em qualquer lugar do programa.
A função start_memlist() é a função que inicializa a lista de memória, e como ela já é chamada dentro da memlist_holder, não é necessário chamá-la novamente.

Como usar a função memcard:

	memcard(void *content, int type, int mallocfree, size_t memsize);
	
	content = conteúdo que será alocado:
	- NULL = aloca um espaço de memória padrão.
	- Qualquer outro tipo de conteúdo será alocado normalmente.

	type = tipo de conteúdo que será alocado:
	- DEFAULT = aloca um espaço de memória padrão.
	- STRING = aloca um espaço de memória para uma STRING.
	- VECTOR = aloca um espaço de memória para um vetor de STRINGS.
	- INTS = aloca um espaço de memória para um vetor de INTEIROS.

	mallocfree = ação que será realizada:
	- MALLOC = aloca um espaço de memória.
	- FREE = libera um espaço de memória.
	- STATUS = exibe o status de um espaço de memória, se ele está alocado ou liberado.
	- PRINT = exibe o endereço de memória de todos os espaços alocados.
	- FREEALL = libera TODAS as alocações de memória.

	memsize = tamanho do espaço de memória que será alocado.

Exemplo de uso:

int main(void)
{
	// É obrigatório chamar essa função no começo do programa para inicializar a lista de memória.
	memlist_holder(start_memlist(), 0); // Inicializa a lista de memória.
	
	char *str = memcard(NULL, STRING, MALLOC, 10); // Aloca um espaço de memória para uma STRING de 10 bytes.
	str = memcard(str, STRING, FREE, 0); // Libera o espaço de memória alocado para a STRING e seta o ponteiro para NULL, evitando double free.
	
	char *str2 = memcard("Hello, World!", STRING, MALLOC, 0); // Aloca um espaço de memória para uma STRING e preenche com "Hello, World!".
	str2 = memcard(str2, STRING, FREE, 0); // Libera o espaço de memória alocado para a STRING e seta o ponteiro para NULL, evitando double free.
	
	char **vector = memcard(NULL, VECTOR, MALLOC, 5); // Aloca um espaço de memória para um vetor de STRINGS de 5 posições.
	vector = memcard(vector, VECTOR, FREE, 0); // Libera o espaço de memória alocado para o vetor de STRINGS e seta o ponteiro para NULL, evitando double free.
	// Também serve para copiar um vetor de STRINGS.
	
	int *ints = memcard(NULL, INTS, MALLOC, 5); // Aloca um espaço de memória para um vetor de INTEIROS de 5 posições.
	ints = memcard(ints, INTS, FREE, 0); // Libera o espaço de memória alocado para o vetor de INTEIROS e seta o ponteiro para NULL, evitando double free.
	// Também serve para copiar um vetor de INTEIROS.
	
	// Podemos também, mallocar as variáveis e só depois liberar a memória toda.
	s = memcard(NULL, STRING, MALLOC, 10);
	s2 = memcard("Hello, World!", STRING, MALLOC, 0);
	v = memcard(NULL, VECTOR, MALLOC, 5);
	i = memcard(NULL, INTS, MALLOC, 5);

	memcard(NULL, FREEALL, FREE, 0); // Libera TODAS as alocações de memória, inclusive a lista encadeada.
	// É obrigatório chamar essa função no final do programa para evitar memory leaks.
*/
