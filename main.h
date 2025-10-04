#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 1024

/* Core printf function */
int _printf(const char *format, ...);

/* Original print functions (without buffer) */
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

/* Buffer-based print functions */
int print_binary_buffer(unsigned int n, char *buffer, int *index);
int print_char_buffer(va_list args, char *buffer, int *index);
int print_string_buffer(va_list args, char *buffer, int *index);
int print_string_special_buffer(va_list args, char *buffer, int *index);
int print_percent_buffer(va_list args, char *buffer, int *index);
int print_number_buffer(unsigned int num, char *buffer, int *index);
int print_integer_buffer(va_list args, char *buffer, int *index);
int print_unsigned_buffer(va_list args, char *buffer, int *index);
int print_octal_buffer(unsigned int num, char *buffer, int *index);
int print_hex_buffer(unsigned int num, char *buffer,
		     int *index, int uppercase);


/* Helper functions */
int _putchar(char c);
/* === flags bitmask === */
#define FLAG_PLUS   (1 << 0)
#define FLAG_SPACE  (1 << 1)
#define FLAG_HASH   (1 << 2)

/* helper to apply prefixes/signs before digits */
int buffer_apply_numeric_flags(long is_neg, unsigned long val,
                               int base, int uppercase, int flags);

#endif
