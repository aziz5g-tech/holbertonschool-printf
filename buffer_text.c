#include "main.h"

/**
 * print_binary_buffer - prints a binary number using buffer
 * @n: the unsigned int number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: The number of printed characters
 */
int print_binary_buffer(unsigned int n, char *buffer, int *index)
{
	int count = 0;

	if (n > 1)
	{
		count += print_binary_buffer(n / 2, buffer, index);
	}

	add_to_buffer((n % 2) + '0', buffer, index);

	return (count + 1);
}

/**
 * print_char_buffer - prints a character using buffer
 * @args: argument list containing the character
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed (1)
 */
int print_char_buffer(va_list args, char *buffer, int *index)
{
	char c = va_arg(args, int);

	add_to_buffer(c, buffer, index);

	return (1);
}

/**
 * print_string_buffer - prints a string using buffer
 * @args: argument list containing the string
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_string_buffer(va_list args, char *buffer, int *index)
{
	char *str = va_arg(args, char *);
	int count = 0;

	if (!str)
	{
		str = "(null)";
	}

	while (*str)
	{
		add_to_buffer(*str, buffer, index);
		str++;
		count++;
	}

	return (count);
}

/**
 * print_percent_buffer - prints a percent sign using buffer
 * @args: argument list (unused)
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed (1)
 */
int print_percent_buffer(va_list args, char *buffer, int *index)
{
	(void)args;
	add_to_buffer('%', buffer, index);

	return (1);
}

/**
 * print_string_special_buffer - prints a string with non-printable chars as \xXX
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
			/* Print non-printable character as \xXX */
			add_to_buffer('\\', buffer, index);
			add_to_buffer('x', buffer, index);

			/* Print hex digits (uppercase, always 2 characters) */
			if ((str[i] / 16) < 10)
			{
				add_to_buffer((str[i] / 16) + '0', buffer, index);
			}
			else
			{
				add_to_buffer((str[i] / 16) - 10 + 'A', buffer, index);
			}

			if ((str[i] % 16) < 10)
			{
				add_to_buffer((str[i] % 16) + '0', buffer, index);
			}
			else
			{
				add_to_buffer((str[i] % 16) - 10 + 'A', buffer, index);
			}

			count += 4;
		}
		else
		{
			/* Print normal printable character */
			add_to_buffer(str[i], buffer, index);
			count++;
		}
	}

	return (count);
}
