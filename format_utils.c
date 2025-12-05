#include "main.h"

/**
 * count_digits - counts number of digits in a number
 * @num: the number
 *
 * Return: number of digits
 */
int count_digits(unsigned long num)
{
    int count = 0;

    if (num == 0)
        return (1);

    while (num > 0)
    {
        count++;
        num /= 10;
    }

    return (count);
}

/**
 * apply_width - applies field width padding
 * @buffer: the buffer
 * @index: buffer index pointer
 * @content_len: length of content to print
 * @is_number: 1 if number, 0 otherwise
 *
 * Return: number of pad chars added
 */
int apply_width(char *buffer, int *index, int content_len, int is_number)
{
    int padding = 0, i;
    char pad_char = ' ';

    if (g_width <= content_len)
        return (0);

    padding = g_width - content_len;

    /* Don't pad if left-aligned (will pad on right later) */
    if (g_flags & FLAG_MINUS)
        return (0);

    /* Use '0' for numbers if FLAG_ZERO and no precision */
    if (is_number && (g_flags & FLAG_ZERO) && g_precision < 0)
        pad_char = '0';

    for (i = 0; i < padding; i++)
        add_to_buffer(pad_char, buffer, index);

    return (padding);
}

/**
 * apply_right_width - applies right padding for left-aligned output
 * @buffer: the buffer
 * @index: buffer index pointer
 * @content_len: length of printed content
 *
 * Return: number of pad chars added
 */
int apply_right_width(char *buffer, int *index, int content_len)
{
    int padding = 0, i;

    if (!(g_flags & FLAG_MINUS) || g_width <= content_len)
        return (0);

    padding = g_width - content_len;

    for (i = 0; i < padding; i++)
        add_to_buffer(' ', buffer, index);

    return (padding);
}

/**
 * apply_precision_zeros - applies precision zeros for numbers
 * @buffer: the buffer
 * @index: buffer index pointer
 * @num_digits: number of digits in the number
 *
 * Return: number of zeros added
 */
int apply_precision_zeros(char *buffer, int *index, int num_digits)
{
    int zeros = 0, i;

    if (g_precision <= num_digits)
        return (0);

    zeros = g_precision - num_digits;

    for (i = 0; i < zeros; i++)
        add_to_buffer('0', buffer, index);

    return (zeros);
}

/**
 * count_octal_digits - counts digits in octal representation
 * @num: the number
 *
 * Return: number of octal digits
 */
int count_octal_digits(unsigned long num)
{
    int count = 0;

    if (num == 0)
        return (1);

    while (num > 0)
    {
        count++;
        num /= 8;
    }

    return (count);
}

/**
 * count_hex_digits - counts digits in hexadecimal representation
 * @num: the number
 *
 * Return: number of hex digits
 */
int count_hex_digits(unsigned long num)
{
    int count = 0;

    if (num == 0)
        return (1);

    while (num > 0)
    {
        count++;
        num /= 16;
    }

    return (count);
}
