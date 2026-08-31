/* Lecture 2 — "Writing the Same Number Three Ways" and "Telling printf What
 * You Handed It".  One value, three notations, and the format codes that get
 * values back out again. */
#include <stddef.h>
#include <stdio.h>

int main(void)
{
    /* All three of these are the SAME number. The prefix only says which
     * notation the digits are written in. */
    int decimal = 42;
    int binary  = 0b101010;   /* 0b is a GCC/Clang extension until C23 */
    int hex     = 0x2A;

    printf("%d  %d  %d   -> all equal? %s\n", decimal, binary, hex,
           (decimal == binary && binary == hex) ? "yes" : "no");

    /* The format code is how printf learns the type it was handed. */
    printf("%%d  signed int        %d\n", -42);
    printf("%%u  unsigned          %u\n", 42u);
    printf("%%c  one character     %c\n", 'A');
    printf("%%s  string            %s\n", "hello");
    printf("%%zu size_t            %zu\n", sizeof(int));
    printf("%%x  hex lower         %x\n", 48879u);
    printf("%%X  hex upper         %X\n", 48879u);
    printf("%%02X padded to two    %02X\n", 5u);
    printf("%%f  double            %f\n", 3.5);
    printf("%%p  pointer           %p\n", (void *)&decimal);
    printf("%%%%  a literal percent %%\n");

    return 0;
}
