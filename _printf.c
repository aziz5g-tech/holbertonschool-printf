#include "main.h"

/* Global bitmask for flags of the current '%' sequence. */
int g_flags = 0;

/**
 * handle_specifier_buffer - handles format specifiers with buffer
 * @c: the format specifier character
 * @args: the argument list
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of printed characters for the specifier
 */
static int handle_specifier_buffer(char c, va_list args,
				   char *buffer, int *index)
{
	if (c == 'c')
		return (print_char_buffer(args, buffer, index));
	else if (c == 's')
		return (print_string_buffer(args, buffer, index));
	else if (c == 'S')
		return (print_string_special_buffer(args, buffer, index));
	else if (c == '%')
		return (print_percent_buffer(args, buffer, index));
	else if (c == 'd' || c == 'i')
		return (print_integer_buffer(args, buffer, index));
	else if (c == 'b')
	{
		unsigned int n = va_arg(args, unsigned int);

		return (print_binary_buffer(n, buffer, index));
	}
	else if (c == 'u')
		return (print_unsigned_buffer(args, buffer, index));
	else if (c == 'o')
	{
		unsigned int n = va_arg(args, unsigned int);

		return (print_octal_buffer(n, buffer, index));
	}
	else if (c == 'x')
	{
		unsigned int n = va_arg(args, unsigned int);

		return (print_hex_buffer(n, buffer, index, 0));
	}
	else if (c == 'X')
	{
		unsigned int n = va_arg(args, unsigned int);

		return (print_hex_buffer(n, buffer, index, 1));
	}

	/* Unknown specifier: print it verbatim. */
	add_to_buffer('%', buffer, index);
	add_to_buffer(c, buffer, index);
	return (2);
}

/**
 * _printf - prints a formatted string
 * @format: the string to format
 *
 * Return: number of printed characters, or -1 if format is NULL
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, count = 0;
	char buffer[BUFFER_SIZE];
	int buffer_index = 0;

	if (!format)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i]; i++)
	{
		if (format[i] == '%')
		{
			int j; /* first char after '%' */

			/* Lone trailing '%' is an error. */
			if (!format[i + 1])
			{
				flush_buffer(buffer, &buffer_index);
				va_end(args);
				return (-1);
			}

			i++;           /* We saw '%' and advanced. */
			j = i;         /* Remember the first char after '%' */

			/* Parse flags (+, space, #) before the specifier. */
			g_flags = 0;
			while (format[i] == '+' || format[i] == ' ' || format[i] == '#')
			{
				if (format[i] == '+')
					g_flags |= FLAG_PLUS;
				else if (format[i] == ' ')
					g_flags |= FLAG_SPACE;
				else /* '#' */
					g_flags |= FLAG_HASH;
				i++;
			}

			/* If specifier is unsupported by flags, treat first char as literal. */
			if (format[i] == '\0' ||
			    format[i] == '%' || format[i] == 'c' ||
			    format[i] == 's' || format[i] == 'S' || format[i] == 'b')
			{
				add_to_buffer('%', buffer, &buffer_index);
				add_to_buffer(format[j], buffer, &buffer_index);
				count += 2;
				i = j;   /* resume after the literal char */
				continue;
			}

			/* Delegate printing with flags available via g_flags. */
			count += handle_specifier_buffer(format[i], args,
							 buffer, &buffer_index);
		}
		else
		{
			add_to_buffer(format[i], buffer, &buffer_index);
			count++;
		}
	}

	flush_buffer(buffer, &buffer_index);
	va_end(args);
	return (count);
}
