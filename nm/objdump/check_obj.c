/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** check objdump
*/

#include <unistd.h>
#include <sys/stat.h>
#include <elf.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include "obj.h"

/**
* Check if file elf 32 bits is correct
* @param elf
* @return true if is correct
*/
static bool check_elf_file32(Elf32_Ehdr *elf)
{
	return !check_ident32(elf) || !check_type32(elf->e_type) ||
		!check_machine32(elf->e_machine) ||
		!check_version32(elf->e_version) ? false : true;
}

/**
* Check if file elf 64 bits is correct
* @param elf
* @return true if is correct
*/
static bool check_elf_file64(Elf64_Ehdr *elf)
{
	return !check_ident64(elf) || !check_type64(elf->e_type) ||
		!check_machine64(elf->e_machine) ||
		!check_version64(elf->e_version) ? false : true;
}

/**
* Check full file and call objdump function 32 bits
* @param elfHdr64 is going to be convert to 32 bits
* @param obj struct containing the exe name and filename
* @param ElfFil FILE*
* @param s stat structure
* @return false if error; else true
*/

bool check_obj32(Elf64_Ehdr *elfHdr64, t_obj *obj, FILE *ElfFil, struct stat *s)
{
	Elf32_Ehdr *elfHdr32 = (Elf32_Ehdr*)elfHdr64;

	if (!check_elf_file32(elfHdr32)) {
		fclose(ElfFil);
		return error_not_recognized(obj);
	}
	if (!get_objdump32(ElfFil, elfHdr32, s, obj->file)) {
		fclose(ElfFil);
		return error_truncated(obj);
	}
	fclose(ElfFil);
	return true;
}

/**
* Check full file and call objdump function 64 bits
* @param elfHdr64 Header of ELF file
* @param obj struct containing the exe name and filename
* @param ElfFil FILE*
* @param s stat structure
* @return false if error; else true
*/
bool check_obj64(Elf64_Ehdr *elfHdr64, t_obj *obj, FILE *ElfFil, struct stat *s)
{
	if (!check_elf_file64(elfHdr64)) {
		fclose(ElfFil);
		return error_not_recognized(obj);
	}
	if (!get_objdump64(ElfFil, elfHdr64, s, obj->file)) {
		fclose(ElfFil);
		return error_truncated(obj);
	}
	fclose(ElfFil);
	return true;
}

/**
* Check Obj file given in Parameters of Main
* @param t_obj structure that contain name of exe, filename
* @return false if error; else true
*/
bool check_obj(t_obj *obj)
{
	struct stat s;
	Elf64_Ehdr elfHdr64;
	FILE *ElfFile = fopen(obj->file, "r");

	if (ElfFile != NULL) {
		if (stat(obj->file, &s)) {
			return error_not_recognized(obj);
		} else if (is_directory(obj->exec, obj->file, &s)) {
			return false;
		}
		if (fread(&elfHdr64, 1, sizeof(Elf64_Ehdr), ElfFile) <
			sizeof(Elf64_Ehdr)) {
			return error_truncated(obj);
		}
		if (elfHdr64.e_ident[EI_CLASS] == ELFCLASS32) {
			return check_obj32(&elfHdr64, obj, ElfFile, &s);
		} else {
			return check_obj64(&elfHdr64, obj, ElfFile, &s);
		}
	} else
		return error_no_such_file(obj);
}
