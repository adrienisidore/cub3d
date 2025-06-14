/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:25:03 by ele-borg          #+#    #+#             */
/*   Updated: 2025/05/29 17:14:35 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "cub3d.h"

/* Fonctions utiles pour créer la chaine répertoriant tous les malloc */

void	*ft_calloc(size_t n, size_t sizof)
{
	unsigned char	*buffer;
	size_t			i;

	if (n < 1 || sizof < 1 || n > SIZE_MAX / sizof)
		return (NULL);
	i = 0;
	buffer = malloc(n * sizof);
	if (buffer == NULL)
		return (NULL);
	while (i < n * sizof)
		buffer[i++] = (unsigned char)0;
	return (buffer);
}

void	gc_init(t_gc *gc)
{
	gc->head = NULL;
}

void	gc_add(t_gc *gc, void *ptr, size_t size)
{
	t_gc_node	*new_node;

	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		perror("allocation failed");
		gc_cleanup(gc);
		free(ptr);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->size = size;
	new_node->next = gc->head;
	gc->head = new_node;
}

void	*gc_malloc(size_t size, t_gc *gc)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("allocation failed");
		gc_cleanup(gc);
		exit(EXIT_FAILURE);
	}
	gc_add(gc, ptr, size);
	return (ptr);
}

void	*gc_calloc(size_t n, size_t sizof, t_gc *gc)
{
	void	*ptr;

	ptr = ft_calloc(n, sizof);
	if (!ptr)
	{
		perror("allocation failed");
		gc_cleanup(gc);
		exit(EXIT_FAILURE);
	}
	gc_add(gc, ptr, n * sizof);
	return (ptr);
}
