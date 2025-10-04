# holbertonschool-printf

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

%o: prefix a single leading 0 for non-zero values → %#o 9 → 011

%x/%X: prefix 0x/0X for non-zero values → %#x 48879 → 0xbeef

Notes

Flags apply only where meaningful; e.g. + and space do not affect %u,
%x, %o, etc.

Edge sequences like "% " or "% % % % " are printed literally as %
(one percent followed by one space each time).
