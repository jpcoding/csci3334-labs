#include <stdint.h>
#include <stdio.h>

int main() {
    // uint8_t is an unsigned 8-bit integer type, which can hold values from 0 to 255.
    // uint8_t has the same size as unsigned char, but it is guaranteed to be 8 bits on all platforms. 
    uint8_t x = 65; // ASCII code for 'A'

    unsigned a = 12;
    unsigned b = 10;
    uint8_t small = (uint8_t)257;

    printf("x as a number: %d\n", x);
    printf("x as a character: %c\n", x);
    printf("x in binary: ");
    for (int i = sizeof(x) * 8 - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    
    printf("\n");
    printf("%u & %u = %u\n", a, b, a & b);
    printf("%u | %u = %u\n", a, b, a | b);
    printf("%u ^ %u = %u\n", a, b, a ^ b);
    printf("%u << 2 = %u\n", a, a << 2);
    printf("257 narrowed to 8 bits: %u\n", (unsigned)small);

    return 0;
}
