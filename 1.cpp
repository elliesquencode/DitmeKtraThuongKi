#include <stdio.h>
#include <stdlib.h>
void capphat(int **p, int n)
{
    *p = (int *)malloc(n * sizeof(int));

    printf("%p", (void *)*p);
}
int main()
{
    int n = 10;
    int *c = NULL;
    capphat(&c, n);
}