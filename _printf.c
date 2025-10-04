#include "main.h"

/* Global bitmask for flags of the current '%' sequence. */
int g_flags = 0;

/**
 * handle_specifier_buffer - handles format specifiers with buffer
 * @c: specifier character
 * @args: argument list
 * @buffer: output buffer
 * @index: pointer to buffer index
 * Return: number of characters produced
 */
static int handle_specifier_buffer(char c, va_list args,char *buffer, int *index)
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
	else
		return (handle_unsigned_specifiers(c, args, buffer, index));
}
/**
 * handle_unsigned_specifiers - handles unsigned, octal, hex, binary
 * @c: specifier character
 * @args: argument list
 * @buffer: output buffer
 * @index: pointer to buffer index
 * Return: number of characters produced
 */
static int handle_unsigned_specifiers(char c, va_list args,char *buffer, int *index)
{
	unsigned int n;

	if (c == 'b')
	{
		n = va_arg(args, unsigned int);
		return (print_binary_buffer(n, buffer, index));
	}
	else if (c == 'u')
		return (print_unsigned_buffer(args, buffer, index));
	else if (c == 'o')
	{
		n = va_arg(args, unsigned int);
		return (print_octal_buffer(n, buffer, index));
	}
	else if (c == 'x' || c == 'X')
	{
		n = va_arg(args, unsigned int);
		return (print_hex_buffer(n, buffer, index, c == 'X'));
	}

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
			int j, k;       /* j: first char after '%', k: look-ahead index */
			int has_spec;   /* 1 if a valid specifier found after flags */

			/* Lone trailing '%' -> error */
			if (!format[i + 1])
			{
				flush_buffer(buffer, &buffer_index);
				va_end(args);
				return (-1);
			}

			i++;            /* We saw '%' and advanced. */
			j = i;

			/*
			 * Look ahead to the eventual specifier to decide
			 * whether a leading space should be treated as a flag.
			 */
			k = i;
			while (format[k] == '+' || format[k] == ' ' || format[k] == '#')
				k++;

			/* If first is space but final specifier isn't d/i: print '%' only now. */
			if (format[i] == ' ' && !(format[k] == 'd' || format[k] == 'i'))
			{
				add_to_buffer('%', buffer, &buffer_index);
				count += 1;
				i = j - 1;    /* next loop will print the space normally */
				continue;
			}

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

			/* Validate that we actually have a supported specifier now. */
			has_spec = 0;
			if (format[i] == 'c' || format[i] == 's' || format[i] == 'S' ||
			    format[i] == '%' || format[i] == 'd' || format[i] == 'i' ||
			    format[i] == 'b' || format[i] == 'u' || format[i] == 'o' ||
			    format[i] == 'x' || format[i] == 'X')
				has_spec = 1;

			/* If nothing valid after flags, print "%<first-after-%>" and continue. */
			if (!has_spec || format[i] == '\0')
			{
				add_to_buffer('%', buffer, &buffer_index);
				add_to_buffer(format[j], buffer, &buffer_index);
				count += 2;
				i = j; /* resume scanning from that character */
				continue;
			}

			/* Delegate printing (flags available via g_flags). */
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
