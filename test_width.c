#include "main.h"
#include <stdio.h>

/**
 * main - test field width for all specifiers
 *
 * Return: 0
 */
int main(void)
{
    int len1, len2;

    printf("=== Testing field width for octal %%o ===\n");
    len1 = printf("STD: [%6o]\n", 42);
    len2 = _printf("MY : [%6o]\n", 42);
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing field width for hex %%x ===\n");
    len1 = printf("STD: [%6x]\n", 255);
    len2 = _printf("MY : [%6x]\n", 255);
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing field width for HEX %%X ===\n");
    len1 = printf("STD: [%6X]\n", 255);
    len2 = _printf("MY : [%6X]\n", 255);
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing field width for char %%c ===\n");
    len1 = printf("STD: [%6c]\n", 'A');
    len2 = _printf("MY : [%6c]\n", 'A');
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing field width for string %%s ===\n");
    len1 = printf("STD: [%6s]\n", "Hi");
    len2 = _printf("MY : [%6s]\n", "Hi");
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing dynamic width %%* ===\n");
    len1 = printf("STD: [%*d]\n", 8, 42);
    len2 = _printf("MY : [%*d]\n", 8, 42);
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing negative dynamic width %%* (left align) ===\n");
    len1 = printf("STD: [%*d]\n", -8, 42);
    len2 = _printf("MY : [%*d]\n", -8, 42);
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    printf("=== Testing with # flag ===\n");
    len1 = printf("STD: [%#8x]\n", 42);
    len2 = _printf("MY : [%#8x]\n", 42);
    printf("STD len: %d, MY len: %d\n\n", len1, len2);

    return (0);
}
