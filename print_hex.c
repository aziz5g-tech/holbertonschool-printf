#include "main.h"

/**
 * print_octal - prints an unsigned integer in octal
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_octal(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	char buf[50];
	int i = 0, count = 0;

	if (n == 0)
		return (_putchar('0'));

	while (n)
	{
		buf[i++] = (n % 8) + '0';
		n /= 8;
	}
	while (i--)
		count += _putchar(buf[i]);

	return (count);
}

/**
 * print_hex_lower - prints an unsigned integer in lowercase hex
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	char buf[50];
	char *hex = "0123456789abcdef";
	int i = 0, count = 0;

	if (n == 0)
		return (_putchar('0'));

	while (n)
	{
		buf[i++] = hex[n % 16];
		n /= 16;
	}
	while (i--)
		count += _putchar(buf[i]);

	return (count);
}

/**
 * print_hex_upper - prints an unsigned integer in uppercase hex
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	char buf[50];
	char *hex = "0123456789ABCDEF";
	int i = 0, count = 0;

	if (n == 0)
		return (_putchar('0'));

	while (n)
	{
		buf[i++] = hex[n % 16];
		n /= 16;
	}
	while (i--)
		count += _putchar(buf[i]);

	return (count);
}
