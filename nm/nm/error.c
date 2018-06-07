/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** error
*/

#include <stdio.h>
#include <stdbool.h>

/**
* Print when the file format is not recognized
* @param exe name of the binary
* @param file name of the file
* @return false
*/
bool error_not_recognized(char *exe, char *file)
{
	printf("%s: %s: File format not recognized\n", exe, file);
	return false;
}

/**
* Print when the file format is truncated
* @param exe name of the binary
* @param file name of the file
* @return false
*/
bool error_truncated(char *exe, char *file)
{
	printf("%s: %s: File truncated\n", exe, file);
	return false;
}

/**
* Print when there is no file
* @param exe name of the binary
* @param file name of the file
* @return false
*/
bool error_no_such_file(char *exe, char *file)
{
	printf("%s: '%s': No such file\n", exe, file);
	return false;
}