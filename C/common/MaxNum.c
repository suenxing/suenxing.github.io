#include <stdio.h>
#include <stdlib.h>
int main()
{
    int a[10], count = 0, maxNum = -__INT32_MAX__;
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &a[i]);
        fflush(stdin);
    }
    for (int i = 0; i < 10; i++)
    {
        if (maxNum < a[i])
        {
            maxNum = a[i];
            count = i;
        }
    }
    printf("%d %d", maxNum, count + 1);
    system("pause");

    return 0;
}