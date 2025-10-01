#include "main.h"

/**
 * print_binary_number - prints a binary number
 * @n: the unsigned long number to print
 *
 * Return: The number of printed characters
 */
static int print_binary_number(unsigned long n)
{
	int count = 0;

	if (n > 1)
		count += print_binary_number(n / 2);

	_putchar((n % 2) + '0');
	return (count + 1);
}

/**
 * handle_specifier - handles format specifiers
 * @c: the format specifier character
 * @args: the argument list
 *
 * Return: The number of printed characters for the specifier
  *
 * Supported specifiers: c, s, %, d, i, b, u, o, x, X
 */
static int handle_specifier(char c, va_list args)
{
    if (c == 'c')
        return (print_char(args));
    else if (c == 's')
        return (print_string(args));
    else if (c == '%')
        return (print_percent(args));
    else if (c == 'd' || c == 'i')
        return (print_integer(args));
    else if (c == 'b')
    {
        unsigned int n = va_arg(args, unsigned int);
        return (print_binary_number(n));
    }
    else if (c == 'u')
        return (print_unsigned(args));
    else if (c == 'o')
        return (print_octal(args));
    else if (c == 'x')
        return (print_hex_lower(args));
    else if (c == 'X')
        return (print_hex_upper(args));

    _putchar('%');
    _putchar(c);
    return (2);
}

/**
 * _printf - prints a formatted string
 * @format: the string to format
 *
 * Return: The number of printed characters, or -1 if format is NULL
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, count = 0;

	if (!format)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i]; i++)
	{
		if (format[i] == '%')
		{
			if (!format[i + 1])
			{
				va_end(args);
				return (-1);
			}
			i++;
			count += handle_specifier(format[i], args);
		}
		else
		{
			_putchar(format[i]);
			count++;
		}
	}

	va_end(args);
	return (count);
}
