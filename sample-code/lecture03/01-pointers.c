/* Lecture 3 — "Pointers Demystified", "Three Things, Kept Straight" and
 * "Two Pointers, One Object". Addresses printed are whatever this run got;
 * they change every time, and that is the point. */
#include <stdio.h>

int main(void)
{
    int x = 42;
    int *p = &x;

    printf("x        = %d\n", x);
    printf("&x       = %p    <- the address of x\n", (void *)&x);
    printf("p        = %p    <- p holds that address\n", (void *)p);
    printf("*p       = %d    <- the value at that address\n", *p);
    printf("*&x      = %d    <- & and * undo each other\n\n", *&x);

    printf("sizeof(x) = %zu bytes, sizeof(p) = %zu bytes\n\n", sizeof x, sizeof p);

    /* Two pointers to one object: aliasing. */
    int *q = &x;
    *p = 99;
    printf("after *p = 99:  x = %d, *q = %d   (one box, two names)\n", x, *q);

    return 0;
}
