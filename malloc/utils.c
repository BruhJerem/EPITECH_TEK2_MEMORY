/*
** EPITECH PROJECT, 2018
** utils
** File description:
** utils
*/

#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

t_block *g_base;

void show_alloc_mem(void) {
	t_block *tmp = g_base;

	my_printf("break: %p\n", sbrk(0));
	while (tmp) {
		if (tmp->free == NOT_FREE) {
			my_printf("%p - %p : %z bytes\n",
				  &tmp->data,
				  &tmp->data + tmp->size,
				  (tmp->size - SIZE / 8 / 8));
		}
		tmp = tmp->next;
	}
}

void *find_location(size_t size)
{
	t_block *block = g_base;

	while (block != NULL) {
		if (block->free == FREE) {
			if (size <= block->size) {
				block->free = NOT_FREE;
				return block->data;
			} else {
				return block+1;
			}
		}
		block = block->next;
	}
	return NULL;
}
