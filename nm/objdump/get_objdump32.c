/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** get_objdump32
*/

#include <elf.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "flags.h"
#include "obj.h"

/**
* Afficher les infos dans les sections
* @param sectHdr section header
* @param data contain infos
*/
void dump_buffer32(Elf32_Shdr *sectHdr, char *data)
{
	size_t	s_off = 0;
	size_t	j = 0;
	size_t	i = 0;
	char buf[16];
	int inc = 0;

	while (s_off < sectHdr->sh_size) {
		printf("%04x", (unsigned int) (sectHdr->sh_addr + inc) * 16);
		for (i = 0; i < 16 && s_off + i < sectHdr->sh_size; i += j) {
			printf(" ");
			for (j = 0; j < 4 && s_off + i + j < sectHdr->sh_size;
			++j) {
				buf[i + j] = dump_byte(data[s_off + i + j]);
			}
		}
		buf[i] = '\0';
		s_off += i;
		inc = align_dump(i, buf, inc);
	}
}

/**
* -s flag print objdump
* @param elfHdr
*/
static void print_s_flag(Elf32_Ehdr *elfHdr)
{
	int fanion = 0;
	char *type = NULL;
	printf ("format de fichier elf32-i386\n");
	printf("architecture: i386:x86, ");
	if (elfHdr->e_type == ET_REL) {
		type = strdup("HAS_RELOC, HAS_SYMS");
		fanion = HAS_RELOC + HAS_SYMS;
	} else if (elfHdr->e_type == ET_EXEC) {
		type = strdup("EXEC_P, HAS_SYMS, D_PAGED");
		fanion = EXEC_P + HAS_SYMS + D_PAGED;
	} else {
		type = strdup("HAS_SYMS, DYNAMIC, D_PAGED");
		fanion = HAS_SYMS + DYNAMIC + D_PAGED;
	}
	printf("fanions 0x%08x:\n", fanion);
	printf("%s\n", type);
	free(type);
	printf("adresse de départ 0x%016x\n\n", (unsigned) elfHdr->e_entry);
}

/**
* Ouvre la section et vérifie si il faut l'afficher
* @param sectHdr
* @param ElfFile
* @param elfHdr
* @param SectNames
*/
static bool print_data(Elf32_Shdr *sectHdr, FILE *ElfFile, Elf32_Ehdr *elfHdr,
			char *SectNames)
{
	uint32_t idx;
	print_s_flag(elfHdr);

	for (idx = 0; idx < elfHdr->e_shnum; idx++) {
		fseek(ElfFile, elfHdr->e_shoff + idx * sizeof(Elf32_Shdr),
			SEEK_SET);
		if (fread(sectHdr, 1, sizeof(Elf32_Shdr), ElfFile)
			< sizeof(Elf32_Shdr))
			return false;
		if ((sectHdr->sh_type == SHT_PROGBITS &&
			strcmp(".note.GNU-stack", SectNames + sectHdr->sh_name)
			!= 0) || elfHdr->e_type == ET_EXEC) {
			if (!print_sect32(sectHdr, SectNames, ElfFile))
				return false;
		}
	}
	return true;
}

/**
* Ouvre le fichier elf et ouvre le Ehdr
* @param ElfFile
* @param elfHdr
* @return true if no error
*/
bool get_objdump32(FILE *ElfFile, Elf32_Ehdr *elfHdr, struct stat *s, char *fil)
{
	char *SectNames;
	Elf32_Shdr sectHdr;
	size_t check;

	fseek(ElfFile, elfHdr->e_shoff + elfHdr->e_shstrndx * sizeof(sectHdr),
		SEEK_SET);
	if (sizeof(sectHdr) > (unsigned) s->st_size) {
		return false;
	}
	check = fread(&sectHdr, 1, sizeof(sectHdr), ElfFile);
	if (check < sizeof(sectHdr)) {
		return false;
	}
	SectNames = malloc(sectHdr.sh_size);
	fseek(ElfFile, sectHdr.sh_offset, SEEK_SET);
	fread(SectNames, 1, sectHdr.sh_size, ElfFile);
	printf("\n%s:   ", fil);
	return print_data(&sectHdr, ElfFile, elfHdr, SectNames);
}
