/* Lecture 3 — "Pointer Arithmetic", "An Array Is Not a Pointer" and
 * "Arrays Decay to Pointers". */
#include <stdio.h>

static void takes_an_array(int a[], size_t n)
{
    /* Your compiler warns on the next line (-Wsizeof-array-argument), which is
     * the whole lesson: you wrote int a[], but a is a pointer, so sizeof gives
     * 8 and not 20. The warning is silenced only so the program can print the
     * number that surprises people. Never silence it in real code. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsizeof-array-argument"
    printf("  inside the function: sizeof(a) = %zu   <- a pointer, not an array\n",
           sizeof a);
#pragma GCC diagnostic pop
    printf("  the length had to be passed separately: n = %zu\n", n);
}

int main(void)
{
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;                     /* the array decays to &arr[0] */

    printf("sizeof(arr) = %zu   sizeof(p) = %zu\n\n", sizeof arr, sizeof p);

    for (int i = 0; i < 5; i++)
        printf("  arr[%d] = %-3d  &arr[%d] = %p\n", i, arr[i], i, (void *)&arr[i]);

    printf("\n+1 on an int * moves %zu bytes:\n", sizeof(int));
    printf("  p     = %p\n", (void *)p);
    printf("  p + 1 = %p\n", (void *)(p + 1));
    printf("  p + 3 = %p\n", (void *)(p + 3));

    printf("\n&arr[3] - &arr[0] = %ld   <- elements, not bytes\n",
           (long)(&arr[3] - &arr[0]));

    *(p + 2) = 99;
    printf("after *(p + 2) = 99:  arr[2] = %d\n", arr[2]);
    printf("a[i] and *(a + i) agree: %d\n\n", arr[2] == *(arr + 2));

    takes_an_array(arr, 5);
    return 0;
}
