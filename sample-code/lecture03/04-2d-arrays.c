/* Lecture 3 — "Two-Dimensional Arrays" and "Why the Order Matters".
 * int a[3][4] is three rows of four, stored one row after the next. */
#include <stdio.h>

int main(void)
{
    int a[3][4];
    int n = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            a[i][j] = n++;

    printf("sizeof(a)    = %zu   <- the whole thing\n", sizeof a);
    printf("sizeof(a[0]) = %zu   <- one row of four ints\n", sizeof a[0]);
    printf("sizeof(a[0][0]) = %zu\n\n", sizeof a[0][0]);

    printf("addresses, walking rows (i outer, j inner):\n");
    for (int i = 0; i < 3; i++) {
        printf("  ");
        for (int j = 0; j < 4; j++)
            printf("%p ", (void *)&a[i][j]);
        printf("  <- row %d\n", i);
    }

    printf("\nthe same twelve slots are one straight run of memory:\n  ");
    int *flat = &a[0][0];
    for (int k = 0; k < 12; k++)
        printf("%d ", flat[k]);

    printf("\n\n&a[1][2] - &a[0][0] = %ld   <- 1*4 + 2, exactly the formula\n",
           (long)(&a[1][2] - &a[0][0]));
    printf("stepping j moves %zu bytes; stepping i moves %zu\n",
           sizeof(int), sizeof a[0]);
    return 0;
}
