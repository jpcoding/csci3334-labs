/* Lecture 2 — bitwise operations doing real work.
 *
 * LeetCode 136, "Single Number": every value in the array appears twice except
 * one. Find it, in one pass, with no extra memory.
 *
 * Three facts from this lecture are the whole solution:
 *     a ^ a == 0      a value cancels itself
 *     a ^ 0 == a      zero leaves a value alone
 *     XOR is commutative and associative, so order does not matter
 *
 * XOR everything together: the pairs annihilate wherever they sit, and the
 * one value without a partner is what is left.
 */
#include <stdio.h>

static int single_number(const int *nums, int n)
{
    int x = 0;
    for (int i = 0; i < n; i++)
        x ^= nums[i];
    return x;
}

int main(void)
{
    int a[] = {5, 5, 1, 2, 2};      /* the array from the slide */
    int b[] = {2, 5, 1, 5, 2};      /* same values, shuffled */
    int c[] = {-5, 8, 8};           /* negatives work too */

    printf("{5,5,1,2,2}  -> %d\n", single_number(a, 5));
    printf("{2,5,1,5,2}  -> %d   same answer, order is irrelevant\n",
           single_number(b, 5));
    printf("{-5,8,8}     -> %d\n", single_number(c, 3));

    /* The running value, step by step — the trace on the slide. */
    printf("\nx = 0\n");
    int x = 0;
    for (int i = 0; i < 5; i++) {
        x ^= a[i];
        printf("  ^ %d  ->  %d\n", a[i], x);
    }

    /* The three facts, checked rather than asserted. */
    printf("\n a ^ a == 0 ?  %d\n", (13 ^ 13) == 0);
    printf(" a ^ 0 == a ?  %d\n", (13 ^ 0) == 13);
    printf(" order free ?  %d\n",
           ((4 ^ 1) ^ 2) == (2 ^ (1 ^ 4)));
    return 0;
}
