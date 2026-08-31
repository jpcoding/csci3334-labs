/* Lecture 2 — "What Two's Complement Means", "Sign Extension", "Truncation"
 * and "Size of Integer Types". */
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static void print_bits8(uint8_t v)
{
    for (int i = 7; i >= 0; i--)
        putchar((v >> i) & 1 ? '1' : '0');
}

int main(void)
{
    /* Two's complement, one step at a time: flip every bit, then add 1. */
    uint8_t five  = 5;
    uint8_t ones  = (uint8_t)~five;        /* one's complement */
    uint8_t twos  = (uint8_t)(ones + 1);   /* two's complement */

    printf("     5 = "); print_bits8(five); putchar('\n');
    printf("    ~5 = "); print_bits8(ones); printf("   one's complement\n");
    printf("  ~5+1 = "); print_bits8(twos);
    printf("   two's complement, read as int8_t = %d\n\n", (int8_t)twos);

    /* Sign extension: widening a signed value copies the sign bit. */
    int8_t  narrow = -1;
    int16_t wide   = narrow;
    printf("int8_t -1 widened to int16_t = %d\n", wide);

    /* Truncation: narrowing to an UNSIGNED type is defined, and is modulo. */
    int16_t big = 257;
    uint8_t cut = (uint8_t)big;
    printf("257 narrowed to uint8_t      = %u   (257 mod 256)\n\n", cut);

    /* Sizes are a property of this platform, not of C. Print them. */
    printf("char      %zu byte\n",  sizeof(char));
    printf("short     %zu bytes\n", sizeof(short));
    printf("int       %zu bytes\n", sizeof(int));
    printf("long      %zu bytes\n", sizeof(long));
    printf("long long %zu bytes\n", sizeof(long long));
    printf("pointer   %zu bytes\n", sizeof(void *));
    printf("CHAR_BIT  %d bits per byte\n\n", CHAR_BIT);

    printf("INT_MAX  %d\nINT_MIN  %d\n", INT_MAX, INT_MIN);
    printf("|INT_MIN| is one larger than INT_MAX, so negating INT_MIN\n");
    printf("overflows — undefined behavior, which is why this file never does it.\n");

    return 0;
}
