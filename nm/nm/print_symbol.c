/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** print symbol of nm
*/

#include <elf.h>
#include <ctype.h>
#include <a.out.h>
#include <stdio.h>
#include "nm.h"

/**
* Array whith all the flags and types and flags (see struct in nm.h)
*/

static t_type const types[] = {{'B', SHT_NOBITS, SHF_ALLOC | SHF_WRITE},
{'R', SHT_PROGBITS, SHF_ALLOC},
{'D', SHT_PROGBITS, SHF_ALLOC | SHF_WRITE},
{'T', SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR},
{'R', SHT_PROGBITS, 0},
{'D', SHT_DYNAMIC, 0}};

/**
* Print the type for the Nm
* @param sym
* @param shdr
* @return char for the type
*/

static char get_type64(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	if (sym.st_shndx == SHN_UNDEF)
		return 'U';
	if (sym.st_shndx == SHN_COMMON)
		return 'C';
	if (sym.st_shndx == SHN_ABS)
		return 'A';
	for (int i = 1; i < 6; i++) {
		if (shdr[sym.st_shndx].sh_type == types[i].type
		&& shdr[sym.st_shndx].sh_flags == types[i].flags) {
			return types[i].ch;
		}
	}
	return 'T';
}

/**
* Function to print the symbol in NM
* @param sym
* @param shdr
* @return the char
*/
char print_symbol64(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char c = get_type64(sym, shdr);

	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) {
		c += 32;
	}
	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	if (ELF64_ST_BIND(sym.st_info) == STB_WEAK
	&& ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	return c;
}

/**
* Print the type for the Nm
* @param sym
* @param shdr
* @return char for the type
*/

static char get_type32(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	if (sym.st_shndx == SHN_UNDEF)
		return 'U';
	if (sym.st_shndx == SHN_COMMON)
		return 'C';
	if (sym.st_shndx == SHN_ABS)
		return 'A';
	for (int i = 1; i < 6; i++) {
		if (shdr[sym.st_shndx].sh_type == types[i].type
		&& shdr[sym.st_shndx].sh_flags == types[i].flags) {
			return types[i].ch;
		}
	}
	return 'T';
}

/**
* Function to print the symbol in NM
* @param sym
* @param shdr
* @return the char
*/
char print_symbol32(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char c = get_type32(sym, shdr);

	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL) {
		c += 32;
	}
	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	if (ELF32_ST_BIND(sym.st_info) == STB_WEAK
	&& ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	return c;
}
