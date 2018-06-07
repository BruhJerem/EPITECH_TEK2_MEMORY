/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** error
*/

#include "obj.h"

/**
* Check if the file of stat is directory
* @param exec
* @param filename
* @param file_infos
* @return true if is directory
*/
bool is_directory(char *exec, char *filename, struct stat *file_infos)
{
	if (!S_ISREG(file_infos->st_mode)) {
		printf("%s: Warning: '%s' is not an ordinary file\n",
			exec, filename);
		return true;
	}
	return false;
}

/**
* Print when the file format is not recognized
* @param exe name of the binary
* @param file name of the file
* @return false
*/
bool error_not_recognized(t_obj *obj)
{
	printf("%s: %s: File format not recognized\n", obj->exec, obj->file);
	return false;
}

/**
* Print when the file format is truncated
* @param exe name of the binary
* @param file name of the file
* @return false
*/
bool error_truncated(t_obj *obj)
{
	printf("%s: %s: File truncated\n", obj->exec, obj->file);
	return false;
}

/**
* Print when there is no file
* @param exe name of the binary
* @param file name of the file
* @return false
*/
bool error_no_such_file(t_obj *obj)
{
	printf("%s: '%s': No such file\n", obj->exec, obj->file);
	return false;
}
