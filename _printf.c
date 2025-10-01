#include "main.h"

/**
 * handle_specifier - handles format specifiers
 * @c: the format specifier character
 * @args: the argument list
 *
 * Return: The number of printed characters for the specifier
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
/**
 * print_binary - prints an unsigned int in binary
 * @args: argument list containing the unsigned int
 *
 * Return: number of characters printed
 */
int print_binary(va_list args)
{
    unsigned int n = va_arg(args, unsigned int);
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    int started = 0, count = 0;

    if (n == 0)
    {
        _putchar('0');
        return (1);
    }

    while (mask)
    {
        if (n & mask)
        {
            _putchar('1');
            count++;
            started = 1;
        }
        else if (started)
        {
            _putchar('0');
            count++;
        }
        mask >>= 1;
    }

    return (count);
}
