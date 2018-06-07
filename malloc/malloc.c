/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "malloc.h"

t_block *g_base = NULL;
static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

static size_t align16(size_t size)
{
	size_t i = 0;

	while ((size + i) % getpagesize() != 0)
		i++;
	i += size;
	return (size_t) i;
}

static void *put_in_head(t_block *block, size_t size)
{
	block->size = size - SIZE;
	block->free = NOT_FREE;
	block->next = g_base;
	g_base = block;
	block->data = block + 1;
	return block;
}

static void *alloc_memory(size_t size)
{
	t_block *ptr;
	size_t size1;

	size1 = align16(size + SIZE);
	ptr = sbrk(size1);
	if (ptr == (void *)-1) {
		pthread_mutex_unlock(&m_mutex);
		return NULL;
	}
	put_in_head(ptr, size1);
	pthread_mutex_unlock(&m_mutex);
	return ptr->data;
}

void *malloc(size_t size)
{
	void *ptr = NULL;

	pthread_mutex_lock(&m_mutex);
	if (size > (size_t)(1 << 31)) {
		pthread_mutex_unlock(&m_mutex);
		return NULL;
	}
	if ((ptr = find_location(size)) != NULL) {
		pthread_mutex_unlock(&m_mutex);
		return ptr;
	} else {
		return alloc_memory(size);
	}
}
