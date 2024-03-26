#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 3
// 目的：分隔字符串，每3个字符插入一个符号
int main()
{
    char str[] = "CatDogDigPotTagMadKidCosZipEar";
    char *st = str;
    char *sp = (char *)malloc(50);
    char *temp = sp;
    for (; *st != '\0';)
    {
        for (int i = 0; i < 3; i++)
            *sp++ = *st++;
        if (*st != '\0')
            *sp++ = ' ';
    }
    *sp++ = '\0';
    sp = temp;
    printf("%s", sp);
    system("pause");
    free(sp);
    free(temp);
    return 0;
}