/* Lecture 2 — "One Byte, Two Readings" and "Characters Are Just Numbers".
 * The byte stores a pattern; the format code decides how you read it. */
#include <stdint.h>
#include <stdio.h>

/* Print the bits of a byte, most significant first. */
static void print_bits(uint8_t v)
{
    for (int i = 7; i >= 0; i--)
        putchar((v >> i) & 1 ? '1' : '0');
}

int main(void)
{
    /* uint8_t is an unsigned 8-bit integer: 0 to 255. It is the same size as
     * unsigned char, but the name promises you the width. */
    uint8_t x = 65;

    printf("x as a number    : %u\n", x);
    printf("x as a character : %c\n", x);
    printf("x in binary      : ");
    print_bits(x);
    printf("   (64 + 1 = 65)\n\n");

    /* ASCII puts the digits together, so subtracting '0' gives the value. */
    char c = '7';
    printf("'%c' has code %d, and c - '0' = %d\n", c, c, c - '0');
    printf("is '%c' a digit? %s\n", c, (c >= '0' && c <= '9') ? "yes" : "no");

    /* The capitals and lowercase are exactly 32 apart — a single bit. */
    printf("'A' = %d, 'a' = %d, difference = %d\n", 'A', 'a', 'a' - 'A');
    printf("'A' | 32 = %c   and   'a' & ~32 = %c\n", 'A' | 32, 'a' & ~32);

    return 0;
}
