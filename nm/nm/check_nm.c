/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** check nm
*/

#include <stdbool.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <unistd.h>
#include <memory.h>
#include "nm.h"

/**
* Check if the file is in the directory
* @param exec name of the execution file
* @param filename name of the filename
* @param file_infos stat info
* @return true if is directory
*/

static bool is_directory(char *exec, char *filename, struct stat *file_infos)
{
	bool return_value = false;

	if (!S_ISREG(file_infos->st_mode)) {
		printf("%s: Warning: '%s' is not an ordinary file\n",
		exec, filename);
		return_value = true;
	}
	return return_value;
}

/**
* Here we need to check if the file is 32 or 64 bit
*/

static bool check_format_file(void *data, char *exec, char *file,
bool is_multiple)
{
	bool return_value = true;
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) data;

	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
		if (check_elf_file32(data)) {
			if (!get_nm32((Elf32_Ehdr *) data, file, is_multiple))
				return_value = error_truncated(exec, file);
		} else
			return_value = error_not_recognized(exec, file);
	} else {
		if (check_elf_file64(data)) {
			if (!get_nm64((Elf64_Ehdr *) data, file, is_multiple))
				return_value = error_truncated(exec, file);
		} else
			return_value = error_not_recognized(exec, file);
	}
	return return_value;
}

/**
* Check nm file given in Parameters of Main
* @param executable name of the executable
* @param filename name of filename
* @param is_multiple if there are more than one in arg main
* @return bool true if the file is correct
*/
bool check_nm(char *exec, char *file, bool is_multiple)
{
	int fd;
	void *data = NULL;
	struct stat file_infos;

	if ((fd = open(file, O_RDONLY)) > 0) {
		if (fstat(fd, &file_infos)) {
			return error_no_such_file(exec, file);
		} else if (is_directory(exec, file, &file_infos)) {
			return false;
		} else if ((data = mmap(0, (size_t)file_infos.st_size, PROT_READ
			, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
			return error_not_recognized(exec, file);
		} else {
			if (!check_format_file(data, exec, file, is_multiple))
				return false;
			munmap(data, (size_t) file_infos.st_size);
		}
		close(fd);
		return true;
	} else
		return error_no_such_file(exec, file);
}
