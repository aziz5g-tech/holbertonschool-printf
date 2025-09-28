#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

/* Writes a single character */
int _putchar(char c)
{
    return write(1, &c, 1);
}

/* Prints a character from va_args */
int print_char(va_list args)
{
    return _putchar((char)va_arg(args, int));
}

/* Prints a string from va_args */
int print_string(va_list args)
{
    char *str = va_arg(args, char *);
    int count = 0;

    if (!str)
        str = "(null)";

    while (*str)
    {
        _putchar(*str++);
        count++;
    }
    return count;
}

/* Prints a percent sign */
int print_percent(va_list args)
{
    (void)args;
    return _putchar('%');
}

/* Main _printf function */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    if (!format)
        return -1;

    va_start(args, format);

    for (int i = 0; format[i]; i++)
    {
        if (format[i] == '%')
        {
            i++;
            if (!format[i])
                break;

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
    return count;
}

