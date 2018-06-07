/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** objdump header
*/

#ifndef PSU_2017_NMOBJDUMP_OBJ_H
	#define PSU_2017_NMOBJDUMP_OBJ_H

	#include <elf.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <sys/stat.h>

typedef struct t_obj {
	char *exec;
	char *file;
} t_obj;

bool check_obj(t_obj *obj);

bool check_ident64(Elf64_Ehdr *elf64);
bool check_ident32(Elf32_Ehdr *elf32);

bool check_type64(Elf64_Half type);
bool check_machine64(Elf64_Half machine);
bool check_version64(Elf64_Word i);

bool check_type32(Elf32_Half type);
bool check_machine32(Elf32_Half machine);
bool check_version32(Elf32_Word i);

bool get_objdump64(FILE *fd, Elf64_Ehdr *elf, struct stat *stat, char *file);
bool get_objdump32(FILE *fd, Elf32_Ehdr *elf, struct stat *stat, char *file);

bool error_not_recognized(t_obj *obj);
bool error_truncated(t_obj *obj);
bool error_no_such_file(t_obj *obj);
bool is_directory(char *exec, char *filename, struct stat *file_infos);

void dump_buffer64(Elf64_Shdr *sectHdr, char *data);
void dump_buffer32(Elf32_Shdr *sectHdr, char *data);

char dump_byte(char b);
int align_dump(size_t i, char *buf, int inc);
bool print_sect64(Elf64_Shdr *sectHdr, const char *SectNames, FILE *ElfFile);
bool print_sect32(Elf32_Shdr *sectHdr, const char *SectNames, FILE *ElfFile);

#endif /* !PSU_2017_NMOBJDUMP_OBJ_H */
