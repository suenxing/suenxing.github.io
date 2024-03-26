#include <stdio.h>
#include <stdlib.h>
size_t hash(const char *str)
{
    size_t seed = 131313;//31 131 1313 13131 131313 etc.. 37
    size_t hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & __SIZE_MAX__);
}
int main()
{
    printf("%llX\n",hash("361128200805276831"));
    system("pause");
    return 0;
}