# _printf

A custom implementation of the C library function `printf`.

## Description

This project is a recreation of the C standard library function `printf`. Our version is called `_printf` and it produces output according to a format as described below. This project was completed as part of the curriculum at Holberton School.

## Prototype

```c
int _printf(const char *format, ...);
```


## Authorized functions and macros
* `write` (man 2 write)
* `malloc` (man 3 malloc)
* `free` (man 3 free)
* `va_start` (man 3 va_start)
* `va_end` (man 3 va_end)
* `va_copy` (man 3 va_copy)
* `va_arg` (man 3 va_arg)


## Format Specifiers

Our `_printf` function handles the following conversion specifiers:

| Specifier | Description |
|-----------|-------------|
| `%c` | Character |
| `%s` | String |
| `%d` | Signed decimal integer |
| `%i` | Signed integer |
| `%%` | Literal percent sign |

### Detailed Format Specifier Descriptions

#### `%c` - Character
- **Function**: `print_char(va_list args)`
- **Purpose**: Prints a single character
- **Input**: Takes an `int` argument (character codes are passed as int in variadic functions)
- **Output**: Prints the corresponding ASCII character
- **Example**: `_printf("Letter: %c\n", 'A');` → `Letter: A`


#### `%s` - String
- **Function**: `print_string(va_list args)`
- **Purpose**: Prints a null-terminated string
- **Input**: Takes a `char *` argument (pointer to string)
- **Special handling**: If the string is `NULL`, prints `(null)`
- **Output**: Prints each character in the string until null terminator
- **Example**: `_printf("Name: %s\n", "John");` → `Name: John`

#### `%d` - Signed Decimal Integer
- **Function**: `print_integer(va_list args)`
- **Purpose**: Prints a signed integer in decimal (base 10) format
- **Input**: Takes an `int` argument
- **Range**: Handles values from `INT_MIN` (-2147483648) to `INT_MAX` (2147483647)
- **Special handling**: Negative numbers are printed with a minus sign
- **Example**: `_printf("Number: %d\n", -42);` → `Number: -42
