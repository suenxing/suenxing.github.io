#include <stdio.h>
#include <stdlib.h>

int isPrime(int n)
{
    if (n == 2 || n == 3)
    {
        return 1;
    }
    if (n % 6 != 1 && n % 6 != 5)
    {
        return 0;
    }

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    FILE *fp = fopen("1.txt", "w");
    fprintf(fp, "switch(n){");
    for (int i = 2; i < 21474836; ++i)
    {
        if (isPrime(i))
        {
            fprintf(fp, "case %lld:", i);
        }
    }
    fprintf(fp, "return 1;default:return 0;}\n");
    fclose(fp);
    system("pause");
    return 0;
}