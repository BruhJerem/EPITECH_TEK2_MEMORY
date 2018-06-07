/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** nm header
*/

#ifndef PSU_2017_NMOBJDUMP_NM_H
	#define PSU_2017_NMOBJDUMP_NM_H

	#include <stdbool.h>
	#include <elf.h>
	#include <stdio.h>

typedef struct t_elf {
	void *strtab;
	void *symtab;
	void *secthdr;
	int nbsym;
} t_elf;

/* Used in print symbol file */
typedef struct s_type {
	char ch;
	uint32_t type;
	uint64_t flags;
} t_type;

bool check_nm(char *executable, char *filename, bool is_multiple);

bool check_ident64(Elf64_Ehdr *elf64);
bool check_ident32(Elf32_Ehdr *elf32);

bool check_type64(Elf64_Half type);
bool check_type32(Elf32_Half type);

bool check_machine64(Elf64_Half machine);
bool check_machine32(Elf32_Half machine);

bool check_version64(Elf64_Word i);
bool check_version32(Elf32_Word i);

bool check_elf_file32(Elf32_Ehdr *elf);
bool check_elf_file64(Elf64_Ehdr *elf);

bool get_nm64(Elf64_Ehdr *data, char *filename, bool is_multiple);
bool get_nm32(Elf32_Ehdr *data, char *filename, bool is_multiple);

char print_symbol64(Elf64_Sym sym, Elf64_Shdr *shdr);
char print_symbol32(Elf32_Sym sym, Elf32_Shdr *shdr);

bool error_not_recognized(char *exe, char *file);
bool error_truncated(char *exe, char *file);
bool error_no_such_file(char *exe, char *file);

#endif /* !PSU_2017_NMOBJDUMP_NM_H */
