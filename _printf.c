#include "main.h"

/* Global bitmask for flags of the current '%' sequence. */
int g_flags = 0;

/**
 * handle_specifier_buffer - dispatches a single conversion to the proper
 *                           buffered printer
 * @c:      conversion specifier
 * @args:   variadic argument list
 * @buffer: output buffer
 * @index:  pointer to current buffer index
 *
 * Return: number of output characters produced for this specifier
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

	/* Unknown specifier: print it literally as "%<c>" */
	add_to_buffer('%', buffer, index);
	add_to_buffer(c, buffer, index);
	return (2);
}

/**
 * _printf - minimalist printf with buffered output
 * @format: format string
 *
 * Return: number of printed characters, or -1 on error
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
			int j, k, has_spec;

			/* lone trailing '%' is invalid */
			if (!format[i + 1])
			{
				flush_buffer(buffer, &buffer_index);
				va_end(args);
				return (-1);
			}

			/* move past '%' and remember the first char after it */
			i++;
			j = i;

			/*
			 * LOOK-AHEAD:
			 * Skip any flags to see the eventual specifier at position k.
			 * If the very first char after '%' is a space but the final
			 * specifier is NOT 'd' or 'i', we should NOT treat the space as a
			 * flag: print only '%' now and let the spaces be handled as normal
			 * characters on the next loop iterations.
			 */
			k = i;
			while (format[k] == '+' || format[k] == ' ' || format[k] == '#')
				k++;

			if (format[i] == ' ' && !(format[k] == 'd' || format[k] == 'i'))
			{
				add_to_buffer('%', buffer, &buffer_index);
				count += 1;

				/* skip all consecutive spaces after '%' */
				while (format[i] == ' ')
					i++;

				/* step back: next loop will process the first non-space */
				i--;
				continue;
			}

			/* parse flags (+, space, #) */
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

			/* validate that we have a supported specifier */
			has_spec = 0;
			if (format[i] == 'c' || format[i] == 's' || format[i] == 'S' ||
			    format[i] == '%' || format[i] == 'd' || format[i] == 'i' ||
			    format[i] == 'b' || format[i] == 'u' || format[i] == 'o' ||
			    format[i] == 'x' || format[i] == 'X')
				has_spec = 1;

			/*
			 * If no valid specifier follows the flags, print "%<first-after-%>"
			 * literally, then continue parsing from that character.
			 * This also safely covers a dangling "% " at end of string.
			 */
			if (!has_spec || format[i] == '\0')
			{
				add_to_buffer('%', buffer, &buffer_index);
				add_to_buffer(format[j], buffer, &buffer_index);
				count += 2;
				i = j;
				continue;
			}

			/* delegate to the per-specifier printer */
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
