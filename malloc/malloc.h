/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
**
*/

#include <stddef.h>

#ifndef PSU_2017_MALLOC_MALLOC_H
# define PSU_2017_MALLOC_MALLOC_H
# define SIZE sizeof(struct t_block)
# define FREE 1
# define NOT_FREE 0

typedef struct t_block {
    size_t size;
    struct t_block *next;
    int free;
    void *data;
}	t_block;

extern t_block *g_base;
void *malloc(size_t size);
void show_alloc_mem(void);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t nsize);
int my_printf(const char *s, ...);
void *find_location(size_t size);

#endif /* PSU_2017_MALLOC_MALLOC_H */
