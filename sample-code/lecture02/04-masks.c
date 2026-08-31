/* Lecture 2 — "Test, Set, Clear, Toggle". One mask, four operations.
 * Bit 0 is the rightmost bit, the ones place. */
#include <stdint.h>
#include <stdio.h>

static void show(const char *label, unsigned v)
{
    printf("%-18s ", label);
    for (int i = 7; i >= 0; i--)
        putchar((v >> i) & 1 ? '1' : '0');
    printf("  = 0x%02X\n", v);
}

int main(void)
{
    unsigned x = 0xAE;              /* 10101110 */
    unsigned mask = 1u << 3;        /* 00001000 — bit 3 only */

    show("x", x);
    show("mask = 1u << 3", mask);
    putchar('\n');

    show("x |  mask  set", x | mask);
    show("x & ~mask  clear", x & ~mask);
    show("x ^  mask  toggle", x ^ mask);
    printf("%-18s %s\n", "x &  mask  test",
           (x & mask) ? "bit 3 is set" : "bit 3 is clear");

    /* Setting a bit that is already set changes nothing — that is the point.
     * These operations do not care what the bit was before. */
    putchar('\n');
    for (int bit = 0; bit < 8; bit++)
        printf("bit %d of 0x%02X is %d\n", bit, x, (x >> bit) & 1);

    return 0;
}
