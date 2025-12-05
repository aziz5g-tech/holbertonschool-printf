#include "main.h"

/**
 * print_octal_formatted - prints octal with field width support
 * @num: number to print
 * @buffer: the buffer
 * @index: buffer index pointer
 *
 * Return: number of characters printed
 */
int print_octal_formatted(unsigned long num, char *buffer, int *index)
{
    int num_digits, total = 0, prefix_len = 0;

    num_digits = count_octal_digits(num);

    /* Check if we need 0 prefix for # flag */
    if ((g_flags & FLAG_HASH) && num != 0)
        prefix_len = 1;

    /* Calculate total content width */
    total = num_digits + prefix_len;
    if (g_precision > num_digits)
        total = g_precision + prefix_len;

    /* Apply left padding */
    if (!(g_flags & FLAG_MINUS))
    {
        char pad = ((g_flags & FLAG_ZERO) && g_precision < 0) ? '0' : ' ';
        int padding = (g_width > total) ? g_width - total : 0;
        int i;

        /* If zero padding and has prefix, print prefix first */
        if (pad == '0' && prefix_len)
        {
            add_to_buffer('0', buffer, index);
            prefix_len = 0;
        }

        for (i = 0; i < padding; i++)
            add_to_buffer(pad, buffer, index);
    }

    /* Print prefix if not printed yet */
    if (prefix_len)
        add_to_buffer('0', buffer, index);

    /* Apply precision zeros */
    apply_precision_zeros(buffer, index, num_digits);

    /* Print the number in octal */
    if (num == 0)
        add_to_buffer('0', buffer, index);
    else
        print_octal_recursive(num, buffer, index);

    /* Apply right padding */
    apply_right_width(buffer, index, total);

    return (g_width > total ? g_width : total);
}

/**
 * print_octal_recursive - recursively prints octal digits
 * @num: number to print
 * @buffer: the buffer
 * @index: buffer index pointer
 *
 * Return: void
 */
void print_octal_recursive(unsigned long num, char *buffer, int *index)
{
    if (num / 8)
        print_octal_recursive(num / 8, buffer, index);
    add_to_buffer((num % 8) + '0', buffer, index);
}

/**
 * print_hex_formatted - prints hex with field width support
 * @num: number to print
 * @buffer: the buffer
 * @index: buffer index pointer
 * @uppercase: 1 for uppercase, 0 for lowercase
 *
 * Return: number of characters printed
 */
int print_hex_formatted(unsigned long num, char *buffer, int *index,
                        int uppercase)
{
    int num_digits, total = 0, prefix_len = 0;

    num_digits = count_hex_digits(num);

    /* Check if we need 0x/0X prefix for # flag */
    if ((g_flags & FLAG_HASH) && num != 0)
        prefix_len = 2;

    /* Calculate total content width */
    total = num_digits + prefix_len;
    if (g_precision > num_digits)
        total = g_precision + prefix_len;

    /* Apply left padding */
    if (!(g_flags & FLAG_MINUS))
    {
        char pad = ((g_flags & FLAG_ZERO) && g_precision < 0) ? '0' : ' ';
        int padding = (g_width > total) ? g_width - total : 0;
        int i;

        /* If zero padding and has prefix, print prefix first */
        if (pad == '0' && prefix_len)
        {
            add_to_buffer('0', buffer, index);
            add_to_buffer(uppercase ? 'X' : 'x', buffer, index);
            prefix_len = 0;
        }

        for (i = 0; i < padding; i++)
            add_to_buffer(pad, buffer, index);
    }

    /* Print prefix if not printed yet */
    if (prefix_len)
    {
        add_to_buffer('0', buffer, index);
        add_to_buffer(uppercase ? 'X' : 'x', buffer, index);
    }

    /* Apply precision zeros */
    apply_precision_zeros(buffer, index, num_digits);

    /* Print the number in hex */
    if (num == 0)
        add_to_buffer('0', buffer, index);
    else
        print_hex_recursive(num, buffer, index, uppercase);

    /* Apply right padding */
    apply_right_width(buffer, index, total);

    return (g_width > total ? g_width : total);
}

/**
 * print_hex_recursive - recursively prints hex digits
 * @num: number to print
 * @buffer: the buffer
 * @index: buffer index pointer
 * @uppercase: 1 for uppercase, 0 for lowercase
 *
 * Return: void
 */
void print_hex_recursive(unsigned long num, char *buffer, int *index,
                         int uppercase)
{
    char hex_char;

    if (num / 16)
        print_hex_recursive(num / 16, buffer, index, uppercase);

    if ((num % 16) < 10)
        hex_char = (num % 16) + '0';
    else
        hex_char = (num % 16) - 10 + (uppercase ? 'A' : 'a');

    add_to_buffer(hex_char, buffer, index);
}
