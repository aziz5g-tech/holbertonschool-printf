#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

int _printf(const char *format, ...);
int _putchar(char c);
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int print_integer(va_list args);
int print_binary(va_list args);
int print_unsigned(va_list args);     
int print_octal(va_list args);       
int print_hex_lower(va_list args); 
int print_hex_upper(va_list args);   
#endif /* MAIN_H */
