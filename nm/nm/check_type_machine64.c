/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** check type machine
*/

#include <stdbool.h>
#include <elf.h>
#include "nm.h"

/**
* check type of Elf file
* @param type of Elf
* @return bool true if type is correct
*/
bool check_type64(Elf64_Half type)
{
	int s[ET_NUM] = {ET_NONE, ET_REL, ET_EXEC, ET_DYN, ET_CORE};

	for (int i = 0; i < ET_NUM; ++i) {
		if (s[i] == type)
			return true;
	}
	return false;
}

/**
* Check Machine of Elf file
* @param machine used of Elf
* @return bool true if machine is correct
*/
bool check_machine64(Elf64_Half machine)
{
	bool ignore;

	for (int i = 0; i < EM_NUM; ++i) {
		if ((i >= 11 && i <= 14) || i == 16 ||
			(i >= 24 && i <= 35) || (i >= 121 && i <= 130) ||
			(i >= 145 && i <= 159) || i == 182 || i == 184 ||
			(i >= 205 && i <= 209) || (i >= 225 && i <= 242) ||
			(i >= 244 && i <= 246)) {
			ignore = true;
		} else {
			ignore = false;
		}
		if (machine == i && !ignore)
			return true;
	}
	return false;
}

/**
* Check version of elf File
* @param version version of Elf
* @return true if version == Current
*/
bool check_version64(Elf64_Word version)
{
	return version == EV_CURRENT ? true : false;
}

/**
* Check all the file elf and call all check function
* @param elf structure elf
* @return bool
*/
bool check_elf_file64(Elf64_Ehdr *elf)
{
	return !check_ident64(elf) || !check_type64(elf->e_type) ||
	!check_machine64(elf->e_machine) ||
	!check_version64(elf->e_version) ? false : true;
}