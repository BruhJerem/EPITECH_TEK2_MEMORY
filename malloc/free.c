/*
** EPITECH PROJECT, 2018
** free
** File description:
** free
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "malloc.h"

t_block *g_base;

void free(void *ptr)
{
	t_block *block = ptr - SIZE;

	if (ptr != NULL) {
		block->free = FREE;
		if (block == g_base) {
			g_base = g_base->next;
		} else {
			memset(ptr, 0, block->size);
		}
	}
}