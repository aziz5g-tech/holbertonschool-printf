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
        count += print_binary_buffer(n / 2, buffer, index);

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
        str = "(null)";

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
    int n = va_arg(args, int);
    unsigned int num;
    int count = 0;

    if (n < 0)
    {
        add_to_buffer('-', buffer, index);
        count++;
        num = (unsigned int)(-(n + 1)) + 1;
    }
    else
    {
        num = n;
    }

    count += print_number_buffer(num, buffer, index);
    return (count);
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
    unsigned int num = va_arg(args, unsigned int);

    return (print_number_buffer(num, buffer, index));
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

    if (num / 16)
        count += print_hex_buffer(num / 16, buffer, index, uppercase);

    if ((num % 16) < 10)
        hex_char = (num % 16) + '0';
    else
        hex_char = (num % 16) - 10 + (uppercase ? 'A' : 'a');

    add_to_buffer(hex_char, buffer, index);
    return (count + 1);
}
int print_string_special_buffer(va_list args, char *buffer, int *index)
{

}
