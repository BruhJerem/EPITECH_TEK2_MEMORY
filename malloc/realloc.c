/*
** EPITECH PROJECT, 2018
** realloc
** File description:
** realloc
*/

#include <memory.h>
#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	void *ptdr;
	t_block *t = ptr - SIZE;

	size = size + 16 - SIZE % 16;
	if (ptr == NULL)
		return (malloc(size));
	if (size <= t->size)
		return (ptr);
	ptdr = malloc(size);
	if (ptdr == NULL)
		return (NULL);
	memcpy(ptdr, ptr, size);
	free(ptr);
	return ptdr;
}
