#include "main.h"

/* Global bitmask for flags of the current '%' sequence. */
int g_flags = 0;
/* Global variable for length modifier of the current '%' sequence. */
int g_length = LENGTH_NONE;
/* Global variables for field width and precision */
int g_width = 0;
int g_precision = -1;
/** * handle_specifier_buffer - handles format specifiers
with buffer * @c: specifier character
* @args: argument list
* @buffer: output buffer
* @index: pointer to buffer index
* Return: number of characters produced */
static int handle_specifier_buffer(char c, va_list args, char *buffer, int *index)
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
		unsigned long n;

		if (g_length == LENGTH_LONG)
			n = va_arg(args, unsigned long);
		else if (g_length == LENGTH_SHORT)
			n = (unsigned short)va_arg(args, unsigned int);
		else
			n = va_arg(args, unsigned int);

		return (print_octal_formatted(n, buffer, index));
	}
	else if (c == 'x')
	{
		unsigned long n;

		if (g_length == LENGTH_LONG)
			n = va_arg(args, unsigned long);
		else if (g_length == LENGTH_SHORT)
			n = (unsigned short)va_arg(args, unsigned int);
		else
			n = va_arg(args, unsigned int);

		return (print_hex_formatted(n, buffer, index, 0));
	}
	else if (c == 'X')
	{
		unsigned long n;

		if (g_length == LENGTH_LONG)
			n = va_arg(args, unsigned long);
		else if (g_length == LENGTH_SHORT)
			n = (unsigned short)va_arg(args, unsigned int);
		else
			n = va_arg(args, unsigned int);

		return (print_hex_formatted(n, buffer, index, 1));
	}
	else if (c == 'p')
		return (print_pointer_buffer(args, buffer, index));
	else if (c == 'r')
		return (print_reversed_buffer(args, buffer, index));
	else if (c == 'R')
		return (print_rot13_buffer(args, buffer, index));

	/* Unknown specifier */
	add_to_buffer('%', buffer, index);
	add_to_buffer(c, buffer, index);
	return (2);
}
/**
 * _printf - prints a formatted string
 * @format: format string
 * Return: printed length, or -1 on error
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
			int j;		  /* j: first char after '%' */
			int has_spec; /* 1 if a valid specifier found after flags */

			/* Lone trailing '%' -> error */
			if (!format[i + 1])
			{
				flush_buffer(buffer, &buffer_index);
				va_end(args);
				return (-1);
			}

			i++; /* We saw '%' and advanced. */
			j = i;

			/* Parse flags (+, space, #, 0, -) before the specifier. */
			g_flags = 0;
			while (format[i] == '+' || format[i] == ' ' || format[i] == '#' ||
				   format[i] == '0' || format[i] == '-')
			{
				if (format[i] == '+')
					g_flags |= FLAG_PLUS;
				else if (format[i] == ' ')
					g_flags |= FLAG_SPACE;
				else if (format[i] == '#')
					g_flags |= FLAG_HASH;
				else if (format[i] == '0')
					g_flags |= FLAG_ZERO;
				else if (format[i] == '-')
					g_flags |= FLAG_MINUS;
				i++;
			} /* Parse field width */
			g_width = 0;
			if (format[i] == '*')
			{
				g_width = va_arg(args, int);
				if (g_width < 0)
				{
					g_flags |= FLAG_MINUS;
					g_width = -g_width;
				}
				i++;
			}
			else
			{
				while (format[i] >= '0' && format[i] <= '9')
				{
					g_width = g_width * 10 + (format[i] - '0');
					i++;
				}
			}

			/* Parse precision */
			g_precision = -1;
			if (format[i] == '.')
			{
				i++;
				if (format[i] == '*')
				{
					g_precision = va_arg(args, int);
					i++;
				}
				else
				{
					g_precision = 0;
					while (format[i] >= '0' && format[i] <= '9')
					{
						g_precision = g_precision * 10 + (format[i] - '0');
						i++;
					}
				}
			} /* Parse length modifiers (l, h). */
			g_length = LENGTH_NONE;
			if (format[i] == 'l')
			{
				g_length = LENGTH_LONG;
				i++;
			}
			else if (format[i] == 'h')
			{
				g_length = LENGTH_SHORT;
				i++;
			}

			/* Validate that we actually have a supported specifier now. */
			has_spec = 0;
			if (format[i] == 'c' || format[i] == 's' || format[i] == 'S' ||
				format[i] == '%' || format[i] == 'd' || format[i] == 'i' ||
				format[i] == 'b' || format[i] == 'u' || format[i] == 'o' ||
				format[i] == 'x' || format[i] == 'X' || format[i] == 'p' ||
				format[i] == 'r' || format[i] == 'R')
				has_spec = 1; /* If nothing valid after flags/length, print "%" and resume. */
			if (!has_spec || format[i] == '\0')
			{
				add_to_buffer('%', buffer, &buffer_index);
				count += 1;
				i = j; /* skip the invalid char after '%' */
				continue;
			} /* Delegate printing (flags available via g_flags). */
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
