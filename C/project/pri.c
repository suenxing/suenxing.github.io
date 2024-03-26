#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(long long n)
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
    int a = 0, p = 0;
    for (long long i = 2; i < LONG_LONG_MAX; ++i)
    {
        a++;
        if (isPrime(i))
        {
            p++;
        }
        printf("%d/%d %llf\n", p, a, (double)p / a);
    }
    system("pause");
    return 0;
}