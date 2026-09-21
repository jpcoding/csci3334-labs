// Operand size, and the one partial-register rule that surprises everyone.
//
// A register has four names (rax / eax / ax / al) and writing through the
// narrow ones does NOT all behave the same way:
//
//     mov rax, v   ->  all 64 bits
//     mov eax, v   ->  low 32 bits, and the top 32 are ZEROED
//     mov ax,  v   ->  low 16 bits, the rest untouched
//     mov al,  v   ->  low  8 bits, the rest untouched
//
// A union over one 8-byte object models exactly that.

#include <stdio.h>
#include <stdint.h>

union reg {
    uint64_t r;     // rax
    uint32_t e;     // eax  (little-endian: overlays the low 4 bytes)
    uint16_t w;     // ax
    uint8_t  b;     // al
};

static void show(const char *label, uint64_t v) {
    printf("  %-28s 0x%016llX\n", label, (unsigned long long)v);
}

int main(void) {
    const uint64_t start = 0xAAAAAAAABBBBBBBBull;
    union reg u;

    puts("start with:");
    show("rax", start);

    puts("\nwrite 0x11 through each name:");

    u.r = start; u.b = 0x11;
    show("mov al,  0x11", u.r);

    u.r = start; u.w = 0x11;
    show("mov ax,  0x11", u.r);

    u.r = start; u.e = 0x11;
    show("mov eax, 0x11   (union)", u.r);
    show("mov eax, 0x11   (real x86)", 0x0000000000000011ull);

    puts("\n  The union keeps the top half. Real x86 ZEROES it.");
    puts("  That is a hardware rule, not a C one -- and it is why compilers");
    puts("  emit `xor eax, eax` to clear all 64 bits of rax in 2 bytes.");

    puts("\nWidening a narrow value (movzx vs movsx):");
    uint8_t byte = 0xFF;
    show("movzx rax, byte  (unsigned)", (uint64_t)(unsigned char)byte);
    show("movsx rax, byte  (signed)",   (uint64_t)(int64_t)(signed char)byte);
    puts("\n  Same byte. The instruction decides whether it meant 255 or -1.");
    return 0;
}
