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
 * print_number - helper function to print a positive number
 * @num: the number to print
 * Return: number of characters printed
 */
static int print_number(unsigned int num)
{
	int count = 0;

	if (num / 10)
		count += print_number(num / 10);

	_putchar((num % 10) + '0');
	count++;

	return (count);
}

/**
 * print_integer - prints an integer
 * @args: argument list
 * Return: number of characters printed
 *///////
int print_integer(va_list args)
{
	int n = va_arg(args, int);
	int count = 0;
	unsigned int num;

	if (n < 0)
	{
		_putchar('-');
		count++;
		num = (unsigned int)(-(n + 1)) + 1;
	}
	else
	{
		num = n;
	}

	count += print_number(num);

	return (count);
}
