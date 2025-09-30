#include "main.h"

/**
 * print_char - prints a character
 * @args: argument list
 * Return: number of characters printed
 */
int print_char(va_list args)
{
	char c = va_arg(args, int);

	_putchar(c);
	return (1);
}

/**
 * print_string - prints a string
 * @args: argument list
 * Return: number of characters printed
 */
int print_string(va_list args)
{
	char *s = va_arg(args, char *);
	int i = 0;

	if (s == NULL)
		s = "(null)";

	while (s[i])
	{
		_putchar(s[i]);
		i++;
	}
	return (i);
}

/**
 * print_percent - prints a percent sign
 * @args: argument list (unused)
 * Return: number of characters printed
 */
int print_percent(va_list args)
{
	(void)args;

	_putchar('%');
	return (1);
}

/**
 * print_integer - prints an integer
 * @args: argument list
 * Return: number of characters printed
 */
int print_integer(va_list args)
{
}
