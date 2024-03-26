#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define W 20
#define H 10

int main()
{
    int x = H / 2, y = W / 2, vx = 1, vy = 1;
    char buf[W];
    memset(buf, '*', W);
    for (;;)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, 0});
        printf("%s\n*", buf);
        for (int i = 0; i < H; printf("*\n"), ++i, printf("*"))
        {
            for (int j = 0; j < W; ++j)
            {
                if ((j == x) && (i == y))
                {
                    printf("O");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("%s\n", buf);

        if ((x >= W - 1) || x <= 1)
        {
            vx = !vx;
        }
        if ((y >= H) || y <= 0)
        {
            vy = !vy;
        }
        x += vx;
        y += vy;
        Sleep(50);
    }
    return 0;
}
