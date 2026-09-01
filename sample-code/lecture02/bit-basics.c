#include <stdint.h>
#include <stdio.h>

int main() {
    // uint8_t is an unsigned 8-bit integer type, which can hold values from 0 to 255.
    // uint8_t has the same size as unsigned char, but it is guaranteed to be 8 bits on all platforms. 
    uint8_t x = 65; // ASCII code for 'A'

    unsigned a = 12;
    unsigned b = 10;
    uint8_t small = (uint8_t)257;
    printf("=========== Testing Unsigned Integers ========\n");
    printf("size of x: %zu bytes\n", sizeof(x));
    printf("x as a number: %d\n", x);
    printf("x as a character: %c\n", x);
    printf("x as an unsigned: %u\n", (unsigned)x);
    printf("x in hexadecimal: 0x%x\n", (unsigned)x);
    printf("x in binary: ");
    for (int i = sizeof(x) * 8 - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");
    printf("=========== Testing Negative Integers ========\n");
    int8_t y = -1; // 8-bit signed integer
    printf("size of y: %zu bytes\n", sizeof(y));
    printf("y as a number: %d\n", y);
    printf("y in hexadecimal: 0x%x\n", (unsigned)y);
    printf("y in binary: ");
    for (int i = sizeof(y) * 8 - 1; i >= 0; i--) {
        printf("%d", (y >> i) & 1);
    }   
    printf("\n");  
    printf("y as an unsigned 8-bit: %u\n", (uint8_t)y);
    printf("y as an unsigned 16-bit: %u\n", (uint16_t)y);
    printf("y as an unsigned 32-bit: %u\n", (uint32_t)y);
    printf("y as a default unsigned: %u\n", (unsigned)y);
 
    
    printf("=========== Testing Bitwise Operations ========\n");

    printf("%u & %u = %u\n", a, b, a & b);
    printf("%u | %u = %u\n", a, b, a | b);
    printf("%u ^ %u = %u\n", a, b, a ^ b);
    printf("%u << 2 = %u\n", a, a << 2);
    printf("257 narrowed to 8 bits: %u\n", (unsigned)small);

    unsigned x_1 = 0xAE;             // 10101110
    printf("x_1 is %u \n", x_1);
    x_1 |=  (1u << 3);               // SET     — bit 3 becomes 1
    printf("x_1 is %u \n", x_1);
    x_1 = 0xAE;    
    x_1 = (x_1 | (1u << 3)) ; 
    printf("x_1 is %u \n", x_1);
    x_1 &= ~(1u << 3);               // CLEAR   — bit 3 becomes 0
    printf("x_1 is %u \n", x_1);
    x_1 ^=  (1u << 3);               // TOGGLE  — bit 3 flips
    if (x_1 & (1u << 3)) { }         // TEST    — nonzero when bit 3 is 1


    return 0;
}
