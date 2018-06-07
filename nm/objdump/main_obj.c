/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** main function
*/

#include <memory.h>
#include "obj.h"
#include <stdlib.h>

/**
* Main for ObjDump
* @return 84 if there is error
*/
int main(int argc, char **argv)
{
	int i;
	t_obj *obj = malloc(sizeof(obj));

	obj->exec = argv[0];
	if (argc < 2) {
		obj->file = "a.out";
		if (!check_obj(obj))
			return 84;
		return 0;
	}
	for (i = 1; argv[i+1] != NULL; i++) {
		obj->file = argv[i];
		check_obj(obj);
	}
	obj->file = argv[i];
	if (!check_obj(obj))
		return 84;
	return 0;
}