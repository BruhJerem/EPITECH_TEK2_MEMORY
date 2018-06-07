/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** main function
*/

#include <memory.h>
#include "nm.h"

/**
* Main Function for NM
* @return 84 if error else 0
*/
int main(int argc, char **argv)
{
	int i;
	bool is_multiple = false;

	if (argc < 2) {
		if (!check_nm(argv[0], "a.out", is_multiple))
			return 84;
		return 0;
	} else if (argc != 2)
		is_multiple = true;
	for (i = 1; argv[i + 1] != NULL ; ++i) {
		check_nm(argv[0], argv[i], is_multiple);
	}
	if (!check_nm(argv[0], argv[i], is_multiple))
		return 84;
	return 0;
}
