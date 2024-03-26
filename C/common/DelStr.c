#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_sub_str(const char *str, const char *sub_str, char *result_str)
{
    int str_len = strlen(str);
    int sub_str_len = strlen(sub_str);
    if (str == NULL)
    {
        result_str = NULL;
        return;
    }

    if (str_len < sub_str_len || sub_str == NULL)
    {
        while (*str != '\0')
            *result_str++ = *str++;
        return;
    }

    while (*str != '\0')
    {
        while (*str != *sub_str && *str != '\0')
            *result_str++ = *str++;
        if (strncmp(str, sub_str, sub_str_len) != 0)
        {
            *result_str++ = *str++;
            continue;
        }
        else
        {
            str += sub_str_len;
        }
    }
    *result_str = '\0';
}
int main()
{
    char *str = (char *)malloc(201);
    char *sub_str = (char *)malloc(21);
    char result[200], ch;
    int len = 0;
    memset(str, '\0', 201);
    memset(sub_str, '\0', 21);
    scanf("%s", sub_str);
    scanf("%s", str);
    delete_sub_str(str, sub_str, result);
    printf("%s\n", result);
    free(str);
    free(sub_str);
    return 0;
}