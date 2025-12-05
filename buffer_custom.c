#include "main.h"

/**
 * print_reversed_buffer - prints a reversed string
 * @args: argument list containing the string
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_reversed_buffer(va_list args, char *buffer, int *index)
{
    char *str = va_arg(args, char *);
    int len = 0, i;

    if (str == NULL)
        str = "(null)";

    /* Calculate string length */
    while (str[len])
        len++;

    /* Print string in reverse */
    for (i = len - 1; i >= 0; i--)
        add_to_buffer(str[i], buffer, index);

    return (len);
}

/**
 * print_rot13_buffer - prints a string encoded in rot13
 * @args: argument list containing the string
 * @buffer: the buffer to use
 * @index: pointer to buffer index
 *
 * Return: number of characters printed
 */
int print_rot13_buffer(va_list args, char *buffer, int *index)
{
    char *str = va_arg(args, char *);
    int i = 0;
    char c;

    if (str == NULL)
        str = "(null)";

    while (str[i])
    {
        c = str[i];

        /* Apply ROT13 transformation */
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
                c += 13;
            else
                c -= 13;
        }

        add_to_buffer(c, buffer, index);
        i++;
    }

    return (i);
}
