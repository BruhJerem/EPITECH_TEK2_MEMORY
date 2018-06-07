/*
** EPITECH PROJECT, 2018
** calloc
** File description:
** calloc
*/

#include <memory.h>
#include <pthread.h>
#include "malloc.h"

void *calloc(size_t nmemb, size_t nsize)
{
	size_t size;
	void *ptr;

	if (!nmemb || !nsize)
		return NULL;
	size = nmemb * nsize;
	if (nsize != size / nmemb)
		return NULL;
	ptr = malloc(size);
	if (!ptr)
		return NULL;
	memset(ptr, 0, size);
	return ptr;
}
