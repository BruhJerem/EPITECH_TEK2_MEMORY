/*
** EPITECH PROJECT, 2018
** printf_utils
** File description:
** printf_utils
*/

#include <unistd.h>

void my_putchar(char c)
{
	write(1, &c, 1);
}

void my_putstr(char *str)
{
	int x = 0;

	while (str[x] != '\0') {
		my_putchar(str[x]);
		x = x + 1;
	}
}

int my_strlen(char *str)
{
	int x = 0;

	while (str[x] != '\0') {
		x = x + 1;
	}
	return x;
}

int my_putnbr(int nb)
{
	if (nb < 0) {
		my_putchar('-');
		nb = -nb;
	}
	if (nb == 0)
		my_putchar('0');
	if (nb / 10 != 0)
		my_putnbr(nb / 10);
	my_putchar((char) ((nb % 10) + '0'));
	return 0;
}

int my_put_nbr_base(unsigned int nb, char *base)
{
	int base_len = my_strlen(base);

	if ((nb / 10) != 0)
		my_put_nbr_base(nb / base_len, base);
	if (nb != 0)
		my_putchar(base[nb % base_len]);
	return 0;
}