#include <stdio.h>
#include <stdlib.h>
unsigned int x32(unsigned int state)
{
    return state ^= (state ^= (state ^= state << 13) >> 17) << 5;
}

int main()
{
    printf("%u", x32(5)%100);
    system("pause");
    return 0;
}
