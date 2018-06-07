/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** utils_dump
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "obj.h"

/**
* Print hexa de char et renvoie char
* @param b
* @return
*/
char dump_byte(char b)
{
	printf("%.2hhx", (unsigned int)b);
	return (char) (isprint(b) ? b : '.');
}

/**
* Allign the dump
* @param i
* @param buf
* @param inc
* @return
*/

int align_dump(size_t i, char *buf, int inc)
{
	size_t bpl = 16;
	size_t len = strlen(buf);

	while (i < bpl) {
		if (i % 4 == 0)
			printf(" ");
		printf("  ");
		i++;
	}
	printf("  %s", buf);
	if (len != bpl) {
		while (len != bpl) {
			printf(" ");
			len++;
		}
	}
	printf("\n");
	return inc++;
}

bool print_sect64(Elf64_Shdr *sectHdr, const char *SectNames, FILE *ElfFile)
{
	if (!sectHdr->sh_name) {
		return true;
	}
	const char *name = SectNames + sectHdr->sh_name;
	fseek(ElfFile, sectHdr->sh_offset, SEEK_SET);
	if (sectHdr->sh_size == 0)
		return true;
	char *data = malloc(sectHdr->sh_size);
	if (fread(data, 1, sectHdr->sh_size, ElfFile)
	< sectHdr->sh_size)
		return false;
	printf("Contenu de la section %s :\n", name);
	dump_buffer64(sectHdr, data);
	free(data);
	return true;
}

bool print_sect32(Elf32_Shdr *sectHdr, const char *SectNames, FILE *ElfFile)
{
	if (!sectHdr->sh_name) {
		return true;
	}
	const char *name = SectNames + sectHdr->sh_name;
	fseek(ElfFile, sectHdr->sh_offset, SEEK_SET);
	if (sectHdr->sh_size == 0)
		return true;
	char *data = malloc(sectHdr->sh_size);
	if (fread(data, 1, sectHdr->sh_size, ElfFile)
	< sectHdr->sh_size)
		return false;
	printf("Contenu de la section %s :\n", name);
	dump_buffer32(sectHdr, data);
	free(data);
	return true;
}
