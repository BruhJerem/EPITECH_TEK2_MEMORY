/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** check type of machine
*/

#include <stdbool.h>
#include <elf.h>

/**
* check type of Elf 64 bits file
* @param type of Elf
* @return bool true if correct
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
* Check Machine of Elf bits file
* @param machine used of Elf
* @return bool true if correct
*/
bool check_machine64(Elf64_Half machine)
{
	bool ignore = false;

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
* Check version of elf bits File
* @param version version of Elf
* @return true if version == Current
*/
bool check_version64(Elf64_Word version)
{
	return version == EV_CURRENT ? true : false;
}