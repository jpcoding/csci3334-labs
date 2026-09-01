/* Lecture 3 — "Strings Are Char Arrays". A string is a char array with a zero
 * byte on the end; nothing else marks where it stops. */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char        arr[] = "hello";   /* writable copy, 6 bytes */
    const char *ptr   = "hello";   /* points at a literal — read-only */

    printf("sizeof(arr) = %zu   <- includes the terminator\n", sizeof arr);
    printf("strlen(arr) = %zu   <- stops before it\n", strlen(arr));
    printf("sizeof(ptr) = %zu   <- just an address\n\n", sizeof ptr);

    printf("byte by byte:\n");
    for (size_t i = 0; i < sizeof arr; i++)
        printf("  arr[%zu] = %3d  %s\n", i, arr[i],
               arr[i] ? (char[]){'\'', arr[i], '\'', 0} : "'\\0'  <- the terminator");

    arr[0] = 'H';                  /* fine: our own array */
    printf("\nafter arr[0] = 'H': %s\n", arr);

    /* ptr[0] = 'H'; would not compile — const says so, and that is the point.
     * Written as plain char *, it would compile and then be undefined at run
     * time, which is far worse. */
    printf("ptr still points at the literal: %s\n", ptr);
    return 0;
}
