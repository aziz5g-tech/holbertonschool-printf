#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 1024

/* Core printf function */
int _printf(const char *format, ...);

/* Print functions */
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int print_integer(va_list args);
int print_unsigned(va_list args);
int print_octal(va_list args);
int print_hex_lower(va_list args);
int print_hex_upper(va_list args);

/* Buffer utility functions */
int flush_buffer(char *buffer, int *index);
int add_to_buffer(char c, char *buffer, int *index);

/* Helper functions */
int _putchar(char c);

#endif /* MAIN_H */
