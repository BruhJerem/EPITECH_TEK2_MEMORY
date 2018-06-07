/*
** EPITECH PROJECT, 2018
** printf
** File description:
** printf
*/

#include <stdarg.h>
#include <unistd.h>
#include "printf.h"

static int my_pointer_address(unsigned int pointer)
{
	my_putstr("0x");
	my_put_nbr_base(pointer, "0123456789abcdef");
	return 0;
}

static void my_put_long_unsigned(long unsigned int nb)
{
	if ((nb / 10) != 0)
		my_put_long_unsigned(nb / 10);
	my_putchar((char) ((nb % 10) + 48));
}

static int specific_1(const char *s, va_list ap, int i)
{
	if (s[i] == '%' || s[i] == '#') {
		if (s[i + 1] == ' ' && s[i + 2] != '%')
			my_putchar(' ');
		while (s[i + 1] == ' ')
			i++;
		if (s[i+1] == 'p')
			my_pointer_address(va_arg(ap, unsigned int));
		else if (s[i+1] == 'z')
			my_put_long_unsigned(va_arg(ap, long unsigned int));
	}
	return 0;
}

int my_printf(const char *s, ...)
{
	int i;
	va_list	ap;
	va_start(ap, s);
	i = 0;
	while (s[i] != '\0') {
		if (s[i] == '%') {
			specific_1(s, ap, i);
			i++;
		} else {
			my_putchar(s[i]);
		}
		i++;
	}
	va_end(ap);
	return 0;
}
