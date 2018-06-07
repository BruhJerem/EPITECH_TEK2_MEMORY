/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** check ident
*/

#include <elf.h>
#include <stdbool.h>
#include <string.h>

/**
* Check Osabi of Elf File
* @param char s
* @return bool true if is correct
*/
static bool check_osabi(char s)
{
	int tab[16] = {ELFOSABI_NONE, ELFOSABI_SYSV, ELFOSABI_HPUX,
			ELFOSABI_NETBSD, ELFOSABI_GNU, ELFOSABI_LINUX,
			ELFOSABI_SOLARIS, ELFOSABI_AIX, ELFOSABI_IRIX,
			ELFOSABI_FREEBSD, ELFOSABI_TRU64, ELFOSABI_MODESTO,
			ELFOSABI_OPENBSD, ELFOSABI_ARM_AEABI, ELFOSABI_ARM,
			ELFOSABI_STANDALONE};
	for (int i = 0; i < 16; ++i) {
		if (tab[i] == s)
			return true;
	}
	return false;
}

/**
* Check class of Elf File
* @param s
* @return bool true if correct
*/
static bool check_class(char s)
{
	int tab[4] = {ELFCLASSNONE, ELFCLASS32, ELFCLASS64, ELFCLASSNUM};

	for (int i = 0; i < 4; ++i) {
		if (tab[i] == s)
			return true;
	}
	return false;
}

/**
* Check Data of Elf File
* @param s
* @return bool true if correct
*/
static bool check_data(char s)
{
	int tab[5] = {EI_DATA, ELFDATANONE, ELFDATA2LSB, ELFDATA2MSB,
			ELFDATANUM};
	for (int i = 0; i < 5; ++i) {
		if (tab[i] == s)
			return true;
	}
	return false;
}

/**
* Check Ident of Elf File 64
* @param elf64
* @return bool true if correct
*/
bool check_ident64(Elf64_Ehdr *elf64)
{
	if (strncmp((const char *)elf64->e_ident, ELFMAG, SELFMAG) != 0)
		return false;
	if (!check_osabi(elf64->e_ident[EI_OSABI]))
		return false;
	if (!check_class(elf64->e_ident[EI_CLASS]))
		return false;
	if (!check_data(elf64->e_ident[EI_DATA]))
		return false;
	return true;
}

/**
* Check Ident of Elf File 32
* @param elf32
* @return bool true if correct
*/
bool check_ident32(Elf32_Ehdr *elf32)
{
	if (strncmp((const char *)elf32->e_ident, ELFMAG, SELFMAG) != 0)
		return false;
	if (!check_osabi(elf32->e_ident[EI_OSABI]))
		return false;
	if (!check_class(elf32->e_ident[EI_CLASS]))
		return false;
	if (!check_data(elf32->e_ident[EI_DATA]))
		return false;
	return true;
}