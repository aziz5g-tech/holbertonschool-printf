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

#### `%i` - Signed Integer
- **Function**: `print_integer(va_list args)`
- **Purpose**: Identical to `%d` - prints a signed integer in decimal format
- **Input**: Takes an `int` argument
- **Note**: In our implementation, `%i` and `%d` behave exactly the same
- **Example**: `_printf("Value: %i\n", 123);` → `Value: 123`

#### `%%` - Literal Percent Sign
- **Function**: `print_percent(va_list args)`
- **Purpose**: Prints a literal percent character
- **Input**: No argument consumed from the argument list
- **Output**: Always prints a single `%` character
- **Example**: `_printf("Progress: 50%%\n");` → `Progress: 50%`


## Usage Examples

```c
#include "main.h"

int main(void)
{
    _printf("Hello, World!\n");
    _printf("Character: %c\n", 'A');
    _printf("String: %s\n", "Hello");
    _printf("Integer: %d\n", 42);
    _printf("Negative: %i\n", -123);
    _printf("Percent: %%\n");
    return (0);
}
```

Output:
```
Hello, World!
Character: A
String: Hello
Integer: 42
Negative: -123
Percent: %
```


## Files

| File | Description |
|------|-------------|
| `_printf.c` | Main printf function |
| `print_functions.c` | Helper functions for different format specifiers |
| `main.h` | Header file with function prototypes |
| `_putchar.c` | Function to write a character to stdout |


## Function Descriptions

### `_printf`
The main function that mimics the behavior of the standard `printf` function. It processes the format string and calls appropriate helper functions based on conversion specifiers.

### `print_char`
Prints a single character.

### `print_string`
Prints a string of characters. If the string is NULL, it prints "(null)".

### `print_integer`
Prints signed integers, handling both positive and negative numbers including edge cases like `INT_MAX` and `INT_MIN`.

### `print_percent`
Prints a literal percent sign.


## Return Value

Upon successful return, `_printf` returns the number of characters printed (excluding the null byte used to end output to strings).

If an error occurs, a negative value is returned.

