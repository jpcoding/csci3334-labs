/* Lecture 3 — "The Stack". Each call gets a frame, and frames march toward
 * lower addresses. Where locals sit INSIDE a frame is the compiler's business,
 * so your numbers will not match your neighbour's. */
#include <stdio.h>

static void inner(int depth)
{
    int local = depth;
    printf("  depth %d: frame local at %p\n", depth, (void *)&local);
    if (depth < 3)
        inner(depth + 1);
}

int main(void)
{
    int a = 1, b = 2, c = 3;

    printf("three locals in one frame:\n");
    printf("  &a = %p  (a = %d)\n", (void *)&a, a);
    printf("  &b = %p  (b = %d)\n", (void *)&b, b);
    printf("  &c = %p  (c = %d)\n", (void *)&c, c);
    printf("  compare with your neighbour — then never rely on the order\n\n");

    printf("each call pushes a new frame, downward:\n");
    inner(1);

    printf("\nmain's frame is up here at %p\n", (void *)&a);
    return 0;
}
