#include "main.h"

/**
 * _printf - prints a formatted string
 * @format: the string to format
 *
 * Return: The number of printed characters, or -1 if format is NULL
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i;
    int count = 0;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (i = 0; format[i]; i++)
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
            if (format[i] == 'c')
                count += print_char(args);
            else if (format[i] == 's')
                count += print_string(args);
            else if (format[i] == '%')
                count += print_percent(args);
            else
            {
                _putchar('%');
                _putchar(format[i]);
                count += 2;
            }
        }
        else
        {
            _putchar(format[i]);
            count++;
        }
    }

    va_end(args);
    return (count);
}
