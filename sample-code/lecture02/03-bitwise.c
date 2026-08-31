/* Lecture 2 — "Bitwise Operations, One Column at a Time", "De Morgan's Laws"
 * and "Shifting Bits". Every operator here works one column at a time. */
#include <stdint.h>
#include <stdio.h>

static void print_bits(uint8_t v)
{
    for (int i = 7; i >= 0; i--)
        putchar((v >> i) & 1 ? '1' : '0');
}

static void show(const char *label, uint8_t v)
{
    printf("%-12s ", label);
    print_bits(v);
    printf("  = %3u\n", v);
}

int main(void)
{
    uint8_t a = 0b1100;   /* 12 */
    uint8_t b = 0b1010;   /* 10 */

    show("a", a);
    show("b", b);
    putchar('\n');
    show("a & b", a & b);
    show("a | b", a | b);
    show("a ^ b", a ^ b);
    show("~a", (uint8_t)~a);
    putchar('\n');

    /* Shifting left by n multiplies by 2^n; right, on an unsigned value,
     * divides. Bits pushed off the end are gone. */
    uint8_t x = 0b00001100;   /* 12 */
    show("x", x);
    show("x << 2", (uint8_t)(x << 2));   /* 48 */
    show("x >> 2", (uint8_t)(x >> 2));   /*  3 */
    putchar('\n');

    /* De Morgan: check the law for every possible pair of bits. */
    printf("De Morgan, all four rows:\n");
    for (int p = 0; p <= 1; p++) {
        for (int q = 0; q <= 1; q++) {
            int lhs = !(p && q);
            int rhs = (!p) || (!q);
            printf("  x=%d y=%d   ~(x & y)=%d   ~x | ~y=%d   %s\n",
                   p, q, lhs, rhs, lhs == rhs ? "agree" : "DIFFER");
        }
    }

    return 0;
}
