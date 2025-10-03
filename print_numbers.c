#include "main.h"

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
 */
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

/**
 * print_unsigned - prints an unsigned integer in base 10
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	int count = 0;
	char buf[50];
	int i = 0;

	if (n == 0)
		return (_putchar('0'));

	while (n)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i--)
		count += _putchar(buf[i]);

	return (count);
}
