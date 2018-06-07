/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** display nm
*/

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <memory.h>
#include "nm.h"

/**
* Print the nm line
* @param elf
* @param j
*/
static bool print_nm(t_elf *elf, int j)
{
	char flag = print_symbol64(((Elf64_Sym *)elf->symtab)[j],
				(Elf64_Shdr *)elf->secthdr);
	char *name = (char *)(elf->strtab +
		((Elf64_Sym *)elf->symtab)[j].st_name);

	if (!name)
		return false;
	if (strcmp("", name) && flag != 'a' && flag != 'A') {
		if (flag == 'U' || flag == 'u' ||
			(((Elf64_Sym *) elf->symtab)[j].st_value == 0 &&
				flag != 't' && flag !=  'T')) {
			printf("%18c %s\n", flag, name);
		} else {
			printf("%016lx %c %s\n",
			((Elf64_Sym *) elf->symtab)[j].st_value,
			flag,
			name);
		}
	}
	return true;
}

static t_elf *get_sect_header64(Elf64_Ehdr *data,
				Elf64_Shdr *section_header_start, char *strings)
{
	Elf64_Shdr section_header;
	t_elf *elf = malloc(sizeof(*elf));

	for (int i = 0; i < data->e_shnum; i++) {
		section_header = section_header_start[i];
		if (section_header.sh_entsize > section_header.sh_size)
			return false;
		if (section_header.sh_type == SHT_SYMTAB) {
			elf->secthdr = section_header_start;
			elf->symtab = (void *)data +
				section_header.sh_offset;
			elf->nbsym = (int) (section_header.sh_size /
				section_header.sh_entsize);
		}
		if (!strcmp(section_header.sh_name + strings, ".strtab")) {
			elf->strtab = (void *)data + section_header.sh_offset;
		}
	}
	return elf;
}

/**
* Function to stock and then print the data of nm
* @param data content of elf64 ehdr
* @param filename name
* @param is_multiple if there more than one in main
* @return true if no error
*/
bool get_nm64(Elf64_Ehdr *data, char *filename, bool is_multiple)
{
	Elf64_Shdr *section_header_start = (Elf64_Shdr *)
		((void *)data + data->e_shoff);
	Elf64_Shdr sections_string = section_header_start[data->e_shstrndx];
	t_elf *elf;
	char *strings = (char *)((void *)data + sections_string.sh_offset);

	elf = get_sect_header64(data, section_header_start, strings);
	if (!elf)
		return false;
	if (is_multiple)
		printf("\n%s:\n", filename);
	if (elf->nbsym == 0)
		return false;
	for (int j = 1; j < elf->nbsym; ++j) {
		if (!print_nm(elf, j))
			return false;
	}
	free(elf);
	return true;
}