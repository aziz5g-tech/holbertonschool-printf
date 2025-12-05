#include "main.h"

/**
 * print_number_buffer - helper function to print number digits
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_number_buffer(unsigned int num, char *buffer, int *index)
{
	int count = 0;

	if (num / 10)
		count += print_number_buffer(num / 10, buffer, index);

	add_to_buffer((num % 10) + '0', buffer, index);
	return (count + 1);
}

/**
 * print_integer_buffer - prints an integer using buffer
 * @args: argument list containing the integer
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_integer_buffer(va_list args, char *buffer, int *index)
{
	long n_long;
	short n_short;
	int n;
	unsigned long num;
	int is_negative = 0, num_digits, total = 0;
	int sign_width = 0;

	if (g_length == LENGTH_LONG)
	{
		n_long = va_arg(args, long);
		is_negative = (n_long < 0);
		num = is_negative ? (unsigned long)(-(n_long + 1)) + 1 : (unsigned long)n_long;
	}
	else if (g_length == LENGTH_SHORT)
	{
		n_short = (short)va_arg(args, int);
		is_negative = (n_short < 0);
		num = is_negative ? (unsigned short)(-(n_short + 1)) + 1 : (unsigned short)n_short;
	}
	else
	{
		n = va_arg(args, int);
		is_negative = (n < 0);
		num = is_negative ? (unsigned int)(-(n + 1)) + 1 : (unsigned int)n;
	}

	num_digits = count_digits(num);

	/* Determine if we need sign/space/plus */
	if (is_negative || (g_flags & FLAG_PLUS) || (g_flags & FLAG_SPACE))
		sign_width = 1;

	/* Calculate total content width (sign + precision zeros + digits) */
	total = num_digits;
	if (g_precision > num_digits)
		total = g_precision;
	total += sign_width;

	/* Apply left padding (if not left-aligned and not zero-padded with sign) */
	if (!(g_flags & FLAG_MINUS) && !((g_flags & FLAG_ZERO) && g_precision < 0 && !is_negative))
		apply_width(buffer, index, total, 0);

	/* Print sign */
	if (is_negative)
		add_to_buffer('-', buffer, index);
	else if (g_flags & FLAG_PLUS)
		add_to_buffer('+', buffer, index);
	else if (g_flags & FLAG_SPACE)
		add_to_buffer(' ', buffer, index);

	/* Apply zero padding if FLAG_ZERO (after sign, before number) */
	if ((g_flags & FLAG_ZERO) && !(g_flags & FLAG_MINUS) && g_precision < 0)
	{
		int zero_pad = g_width - total;
		int i;

		for (i = 0; i < zero_pad; i++)
			add_to_buffer('0', buffer, index);
	}

	/* Apply precision zeros */
	apply_precision_zeros(buffer, index, num_digits);

	/* Print the number */
	if (g_length == LENGTH_LONG)
		print_long_buffer(num, buffer, index);
	else if (g_length == LENGTH_SHORT)
		print_short_buffer((unsigned short)num, buffer, index);
	else
		print_number_buffer((unsigned int)num, buffer, index);

	/* Apply right padding for left-aligned */
	apply_right_width(buffer, index, total);

	return (g_width > total ? g_width : total);
}

/**
 * print_unsigned_buffer - prints an unsigned integer using buffer
 * @args: argument list containing the unsigned integer
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_unsigned_buffer(va_list args, char *buffer, int *index)
{
	unsigned int num;
	unsigned long num_long;
	unsigned short num_short;

	if (g_length == LENGTH_LONG)
	{
		num_long = va_arg(args, unsigned long);
		return (print_long_buffer(num_long, buffer, index));
	}
	else if (g_length == LENGTH_SHORT)
	{
		num_short = (unsigned short)va_arg(args, unsigned int);
		return (print_short_buffer(num_short, buffer, index));
	}
	else
	{
		num = va_arg(args, unsigned int);
		return (print_number_buffer(num, buffer, index));
	}
}

/**
 * print_octal_buffer - prints an octal number using buffer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_octal_buffer(unsigned int num, char *buffer, int *index)
{
	int count = 0;

	/* With '#', emit a single leading '0' for non-zero octal values (once). */
	if ((num != 0) && (g_flags & FLAG_HASH) && (num / 8 == 0))
		count += add_to_buffer('0', buffer, index);

	if (num / 8)
		count += print_octal_buffer(num / 8, buffer, index);

	add_to_buffer((num % 8) + '0', buffer, index);
	return (count + 1);
}

/**
 * print_hex_buffer - prints a hexadecimal number using buffer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 * @uppercase: 1 for uppercase, 0 for lowercase
 *
 * Return: number of characters printed
 */
int print_hex_buffer(unsigned int num, char *buffer, int *index, int uppercase)
{
	int count = 0;
	char hex_char;

	/* With '#', emit '0x'/'0X' for non-zero hex values (printed once). */
	if ((num != 0) && (g_flags & FLAG_HASH) && (num / 16 == 0))
	{
		count += add_to_buffer('0', buffer, index);
		count += add_to_buffer(uppercase ? 'X' : 'x', buffer, index);
	}

	if (num / 16)
		count += print_hex_buffer(num / 16, buffer, index, uppercase);

	if ((num % 16) < 10)
		hex_char = (num % 16) + '0';
	else
		hex_char = (num % 16) - 10 + (uppercase ? 'A' : 'a');

	add_to_buffer(hex_char, buffer, index);
	return (count + 1);
}

/**
 * print_hex_ptr - prints a hexadecimal number for pointer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
static int print_hex_ptr(unsigned long num, char *buffer, int *index)
{
	int count = 0;
	char hex_char;

	if (num / 16)
		count += print_hex_ptr(num / 16, buffer, index);

	if ((num % 16) < 10)
		hex_char = (num % 16) + '0';
	else
		hex_char = (num % 16) - 10 + 'a';

	add_to_buffer(hex_char, buffer, index);
	return (count + 1);
}

/**
 * print_pointer_buffer - prints a pointer address using buffer
 * @args: argument list containing the pointer
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_pointer_buffer(va_list args, char *buffer, int *index)
{
	void *ptr = va_arg(args, void *);
	unsigned long address;
	int count = 0;

	if (ptr == NULL)
	{
		char *nil_str = "(nil)";
		int i;

		for (i = 0; nil_str[i]; i++)
			add_to_buffer(nil_str[i], buffer, index);
		return (5);
	}

	/* Cast pointer to unsigned long */
	address = (unsigned long)(size_t)ptr;

	/* Print "0x" prefix */
	add_to_buffer('0', buffer, index);
	add_to_buffer('x', buffer, index);
	count = 2;

	/* Print the address in hexadecimal */
	count += print_hex_ptr(address, buffer, index);

	return (count);
}

/**
 * print_long_buffer - prints an unsigned long number
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_long_buffer(unsigned long num, char *buffer, int *index)
{
	int count = 0;

	if (num / 10)
		count += print_long_buffer(num / 10, buffer, index);

	add_to_buffer((num % 10) + '0', buffer, index);
	return (count + 1);
}

/**
 * print_short_buffer - prints an unsigned short number
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_short_buffer(unsigned short num, char *buffer, int *index)
{
	int count = 0;

	if (num / 10)
		count += print_short_buffer(num / 10, buffer, index);

	add_to_buffer((num % 10) + '0', buffer, index);
	return (count + 1);
}

/**
 * print_octal_long_buffer - prints an octal long number using buffer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_octal_long_buffer(unsigned long num, char *buffer, int *index)
{
	int count = 0;

	if ((num != 0) && (g_flags & FLAG_HASH) && (num / 8 == 0))
		count += add_to_buffer('0', buffer, index);

	if (num / 8)
		count += print_octal_long_buffer(num / 8, buffer, index);

	add_to_buffer((num % 8) + '0', buffer, index);
	return (count + 1);
}

/**
 * print_octal_short_buffer - prints an octal short number using buffer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_octal_short_buffer(unsigned short num, char *buffer, int *index)
{
	int count = 0;

	if ((num != 0) && (g_flags & FLAG_HASH) && (num / 8 == 0))
		count += add_to_buffer('0', buffer, index);

	if (num / 8)
		count += print_octal_short_buffer(num / 8, buffer, index);

	add_to_buffer((num % 8) + '0', buffer, index);
	return (count + 1);
}

/**
 * print_hex_long_buffer - prints a long hexadecimal number using buffer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 * @uppercase: 1 for uppercase, 0 for lowercase
 *
 * Return: number of characters printed
 */
int print_hex_long_buffer(unsigned long num, char *buffer,
						  int *index, int uppercase)
{
	int count = 0;
	char hex_char;

	if ((num != 0) && (g_flags & FLAG_HASH) && (num / 16 == 0))
	{
		count += add_to_buffer('0', buffer, index);
		count += add_to_buffer(uppercase ? 'X' : 'x', buffer, index);
	}

	if (num / 16)
		count += print_hex_long_buffer(num / 16, buffer, index, uppercase);

	if ((num % 16) < 10)
		hex_char = (num % 16) + '0';
	else
		hex_char = (num % 16) - 10 + (uppercase ? 'A' : 'a');

	add_to_buffer(hex_char, buffer, index);
	return (count + 1);
}

/**
 * print_hex_short_buffer - prints a short hexadecimal number using buffer
 * @num: number to print
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 * @uppercase: 1 for uppercase, 0 for lowercase
 *
 * Return: number of characters printed
 */
int print_hex_short_buffer(unsigned short num, char *buffer,
						   int *index, int uppercase)
{
	int count = 0;
	char hex_char;

	if ((num != 0) && (g_flags & FLAG_HASH) && (num / 16 == 0))
	{
		count += add_to_buffer('0', buffer, index);
		count += add_to_buffer(uppercase ? 'X' : 'x', buffer, index);
	}

	if (num / 16)
		count += print_hex_short_buffer(num / 16, buffer, index, uppercase);

	if ((num % 16) < 10)
		hex_char = (num % 16) + '0';
	else
		hex_char = (num % 16) - 10 + (uppercase ? 'A' : 'a');

	add_to_buffer(hex_char, buffer, index);
	return (count + 1);
}
