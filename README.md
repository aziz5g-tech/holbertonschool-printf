# _printf

A buffered reimplementation of the C library `printf`.  
Prints to **stdout** and returns the number of characters written (or `-1` on error).

---

## Build & Usage

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 \
    _printf.c _putchar.c \
    buffer_utils.c buffer_numeric.c \
    buffer_text_basic.c buffer_text_special.c \
    print_basic.c print_hex.c print_numbers.c \
    -o test_printf
c
Copy code
#include "main.h"

int main(void)
{
    _printf("Hello %s! Number = %+d, hex = %#x\n", "world", 7, 48879);
    return (0);
}
Description
_printf supports a subset of the standard conversion specifiers and three
non-length flags.

Supported specifiers
Specifier	Meaning
%c	Character
%s	String
%S	String with non-printables as \xHH
%%	Literal percent sign
%d %i	Signed decimal integer
%b	Unsigned integer in binary
%u	Unsigned decimal integer
%o	Unsigned octal
%x	Unsigned hex (lowercase)
%X	Unsigned hex (UPPERCASE)

Flags
The following flag characters are handled for non-custom conversions:

+ — For %d/%i, always prefix a sign; e.g. %+d → +7.

(space) — For %d/%i, prefix a single space if no sign is written;
e.g. % d → 7. The + flag takes precedence over space.

# — Alternate form

%o: prefix a single leading 0 for non-zero values → %#o 9 prints 011

%x/%X: prefix 0x/0X for non-zero values → %#x 48879 prints 0xbeef

Notes

Flags apply only where meaningful; e.g. + and space do not affect %u,
%x, %o, etc.

Edge sequences like "% " or "% % % % " are printed literally as %
(one percent followed by one space each time).

Return Value
_printf returns the number of characters printed (excluding the terminating
null byte). If format is NULL or a fatal error occurs, -1 is returned.

Examples
c
Copy code
_printf("%+d\n", 7);          /* +7              */
_printf("% d\n", 7);          /*  7              */
_printf("% d\n", -7);         /* -7 (space ignored when sign exists) */
_printf("%#o\n", 9);          /* 011             */
_printf("%#x\n", 48879);      /* 0xbeef          */
_printf("%#X\n", 48879);      /* 0XBEEF          */
_printf("% % % % \n");        /* % % % %         */
Files
main.h – public API, prototypes, and flag bitmasks

_printf.c – core dispatcher and flag parsing

buffer_*.c – buffered numeric/text helpers

print_*.c – non-buffer helpers used by some specs

_putchar.c – low-level write wrapper

man_3_printf – manual page for _printf

Authors
Lina (linawsm52), Abdulaziz (aziz5g-tech), Nourah (noneals)
