#include <stdio.h>
#include <stdlib.h>
int fun(char str[])
{
    int value = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        value += str[i] - '0';
        value *= 10;
    }
    value /= 10;
    return value;
}
int main()
{
    char str[10];
    // scanf("%s", str);
    gets(str);
    printf("%d", fun(str));
    system("pause");
    return 0;
}