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
static void print_nm(t_elf *elf, int j)
{
	char flag = print_symbol32(((Elf32_Sym *)elf->symtab)[j],
			(Elf32_Shdr *)elf->secthdr);
	char *name = (char *)(elf->strtab +
		((Elf64_Sym *)elf->symtab)[j].st_name);

	if (strcmp("", name) && flag != 'a' && flag != 'A') {
		if (flag == 'U' || flag == 'u' ||
			(((Elf64_Sym *) elf->symtab)[j].st_value == 0 &&
				flag != 't' && flag !=  'T')) {
			printf("%18c %s\n", flag, name);
		} else {
			printf("%016lx %c %s\n",
			(unsigned long) ((Elf32_Sym *)
				elf->symtab)[j].st_value,
			flag,
			name);
		}
	}
}

static t_elf *get_sect_header32(Elf32_Ehdr *data,
				Elf32_Shdr *section_header_start, char *strings)
{
	Elf32_Shdr section_header;
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
bool get_nm32(Elf32_Ehdr *data, char *filename, bool is_multiple)
{
	Elf32_Shdr *section_header_start = (Elf32_Shdr *)
		((void *)data + data->e_shoff);
	Elf32_Shdr sections_string = section_header_start[data->e_shstrndx];
	char *strings = (char *)((void *)data + sections_string.sh_offset);
	t_elf *elf;

	elf = get_sect_header32(data, section_header_start, strings);
	if (!elf)
		return false;
	if (is_multiple)
		printf("\n%s:\n", filename);
	for (int j = 1; j < elf->nbsym; ++j) {
		print_nm(elf, j);
	}
	free(elf);
	return true;
}