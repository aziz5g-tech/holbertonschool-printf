#include "main.h"

/**
 * print_hex_char_buffer - prints a character in hexadecimal format (\xXX)
 * @c: the character to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed (always 4)
 */
static int print_hex_char_buffer(char c, char *buffer, int *index)
{
	/* Print \x prefix */
	add_to_buffer('\\', buffer, index);
	add_to_buffer('x', buffer, index);

	/* Print first hex digit */
	if ((c / 16) < 10)
	{
		add_to_buffer((c / 16) + '0', buffer, index);
	}
	else
	{
		add_to_buffer((c / 16) - 10 + 'A', buffer, index);
	}

	/* Print second hex digit */
	if ((c % 16) < 10)
	{
		add_to_buffer((c % 16) + '0', buffer, index);
	}
	else
	{
		add_to_buffer((c % 16) - 10 + 'A', buffer, index);
	}

	return (4);
}

/**
 * print_string_special_buffer - prints string with non-printable chars as \xXX
 * @args: argument list containing the string
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_string_special_buffer(va_list args, char *buffer, int *index)
{
	char *str = va_arg(args, char *);
	int count = 0;
	int i;

	if (!str)
	{
		str = "(null)";
	}

	for (i = 0; str[i]; i++)
	{
		if (str[i] > 0 && (str[i] < 32 || str[i] >= 127))
		{
			count += print_hex_char_buffer(str[i], buffer, index);
		}
		else
		{
			add_to_buffer(str[i], buffer, index);
			count++;
		}
	}

	return (count);
}
