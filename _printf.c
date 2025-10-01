#include "main.h"
static int print_binary_number(unsigned long n) 
{
int count = 0;
if (n > 1) count += print_binary_number(n / 2);
_putchar((n % 2) + '0'); 
return count + 1; 
}
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
	else if (c == 'b') 
	{ 
		long val = va_arg(args, long);
	unsigned long n = (unsigned long)val;
	return print_binary_number(n); 
	}

        _putchar('0');
        return 1;
    }
    return print_binary_number(n);
}
        _putchar('0');
        return 1;
    }
    return print_binary_number(n);
}
        _putchar('0');
        return 1;
    }
    return print_binary_number(n);
}


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

