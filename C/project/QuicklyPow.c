#include <stdio.h>
#include <stdlib.h>
int mp(int x, int y)
{
    int r = 1;
    while (y != 0)
    {
        if (y & 1)
            r *= x;
        x *= x;
        y >>= 1;
    }
    return r;
}
int main()
{
    printf("%d", mp(2, 21));
    system("pause");
    return 0;
}