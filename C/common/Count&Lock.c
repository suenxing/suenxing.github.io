#include <stdio.h>
#include <stdlib.h>

unsigned int len = 0, maxlen = 100, word = 0, num = 0, other = 0;

void count(char *s)
{
    for (unsigned int i = 0; i < len; ++i)
    {
        if ('0' <= s[i] && s[i] <= '9')
        {
            ++num;
        }
        else if (('A' <= s[i] && s[i] <= 'Z') || ('a' <= s[i] && s[i] <= 'z'))
        {
            ++word;
        }
        else
        {
            ++other;
        }
    }
}
void code(char *s)
{
    for (unsigned int i = 0; i < len; ++i)
    {
        if (('A' <= s[i] && s[i] <= 'Z'))
        {
            if (s[i] + 4 <= 'Z')
            {
                s[i] += 4;
            }
            else
            {
                s[i] = (s[i] + 4) % 90 + 64;
            }
        }
        else if (('a' <= s[i] && s[i] <= 'z'))
        {
            if (s[i] + 4 <= 'z')
            {
                s[i] += 4;
            }
            else
            {
                s[i] = (s[i] + 4) % 122 + 96;
            }
        }
        else
        {
            continue;
        }
    }
}
int main()
{
    char ch;
    char *str = (char *)calloc(maxlen, sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        str[len++] = ch;
        if (len > maxlen)
        {
            maxlen += 50;
            str = (char *)realloc(str, maxlen);
        }
    }
    count(str);
    printf("字母: %d\n数字: %d\n其余: %d\n\n原文: %s\n", word, num, other, str);
    code(str);
    printf("密文: %s", str);
    system("pause");
    return 0;
}
