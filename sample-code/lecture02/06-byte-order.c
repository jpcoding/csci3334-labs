/* Lecture 2 — "Byte Ordering (Endianness)". A multi-byte value has to be laid
 * out in some order. Ask your own machine which one it uses. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int x = 1;

    /* Looking at any object through unsigned char * is allowed in C, and is
     * how you inspect the bytes something is actually made of. */
    if (*(unsigned char *)&x == 1)
        printf("This machine is little-endian.\n\n");
    else
        printf("This machine is big-endian.\n\n");

    /* Lay the four bytes of a value out, lowest address first. */
    uint32_t v = 0xDEADBEEF;
    unsigned char bytes[sizeof v];
    memcpy(bytes, &v, sizeof v);

    printf("uint32_t v = 0x%08X\n", v);
    for (size_t i = 0; i < sizeof v; i++)
        printf("  byte at +%zu : %02X\n", i, bytes[i]);

    printf("\nOn a little-endian machine the low byte, EF, comes first.\n");
    printf("The value is the same either way — only the layout differs.\n");

    return 0;
}
