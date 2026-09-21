// `lea` computes an address expression and hands you the number.
//
// Because the address form is `Base + Index*Scale + Disp`, any multiply by
// 2, 3, 4, 5, 8 or 9 is one `lea` — no multiplier, no memory access. This is
// why `lea` shows up all over compiler output in code that has no pointers
// in it at all.
//
//     make asm   ->  look for the `lea` in each function

#include <stdio.h>

long times2(long x) { return x * 2; }   // lea rax, [rdi + rdi]
long times3(long x) { return x * 3; }   // lea rax, [rdi + rdi*2]
long times5(long x) { return x * 5; }   // lea rax, [rdi + rdi*4]
long times9(long x) { return x * 9; }   // lea rax, [rdi + rdi*8]

// 7 is not Base + Index*Scale, but 8x - x is. Two instructions, still no imul.
long times7(long x) { return x * 7; }   // lea rax, [8*rdi]  then  sub rax, rdi

// The address-expression form, used as arithmetic: 4 + 8*i + 3
long affine(long i) { return 8 * i + 7; }

int main(void) {
    long x = 6;
    printf("x        = %ld\n", x);
    printf("times2   = %ld\n", times2(x));
    printf("times3   = %ld\n", times3(x));
    printf("times5   = %ld\n", times5(x));
    printf("times9   = %ld\n", times9(x));
    printf("times7   = %ld   <- lea cannot do 7 alone: lea then sub\n", times7(x));
    printf("affine   = %ld\n", affine(x));
    return 0;
}
