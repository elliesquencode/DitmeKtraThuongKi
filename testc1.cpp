#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int sum(int n)
{
    if (n < 10)
        return n;
    return (n % 10) + sum(n / 10);
}

bool isPerPrime(int n)
{
    if (isPrime(n) == 0)
        return false;
    if (isPrime(n) == 1)
    {
        if (isPrime(sum(n) == 0))
            return false;
        if (n < 10 && isPrime(n) == 1)
            return true;
    }
    return isPerPrime(sum(n));
}

int *generatePerfectPrime(int n)
{
    int *PerfectPrime = (int *)malloc(n * sizeof(int));
    if (!PerfectPrime)
        return NULL;
    int currentPrime = 2;
    int idx = 0;
    while (idx < n)
    {
        if (isPerPrime(currentPrime))
            PerfectPrime[idx++] = currentPrime;
        currentPrime++;
    }
    return PerfectPrime;
}

void printAndWrite(int *PerfectPrime, int n, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("khong the mo file.\n");
        return;
    }
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", PerfectPrime[i]);
        fprintf(fp, "%d ", PerfectPrime[i]);
    }
    printf("\n");
    fclose(fp);
}

int main()
{
    int n = 10;
    char name[30];
    printf("nhap ten tep can mo: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int *perfectPrime = generatePerfectPrime(n);
    if (!perfectPrime)
    {
        printf("khong the tao bo nho dong");
        return 1;
    }
    printAndWrite(perfectPrime, n, name);
    free(perfectPrime);

    return 0;
}