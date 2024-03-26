#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#define size 30
short board[size][size];
short x = size >> 1, y = size >> 1;
_Bool player = false;

void PanDing()
{
    short shu = 1, heng = 1, pie = 1, na = 1;

    for (short i = 1; i <= 4; i++)
    {
        if (board[y + i][x] == board[y][x] && board[y][x])
            shu++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y - i][x] == board[y][x] && board[y][x])
            shu++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y][x - i] == board[y][x] && board[y][x])
            heng++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y][x + i] == board[y][x] && board[y][x])
            heng++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y + i][x - i] == board[y][x] && board[y][x])
            pie++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y - i][x + i] == board[y][x] && board[y][x])
            pie++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y + i][y + i] == board[y][x] && board[y][x])
            na++;
        else
            break;
    }

    for (short i = 1; i <= 4; i++)
    {
        if (board[y - i][x - i] == board[y][x] && board[y][x])
            na++;
        else
            break;
    }

    if (shu == 5 || heng == 5 || pie == 5 || na == 5)
    {
        if (board[y][x] == 2)
        {
            printf("白子胜");
            system("pause");
            exit(0);
        }
        else
        {
            printf("黑子胜!");
            system("pause");
            exit(0);
        }
    }
}
void Drop()
{
    switch (getch())
    {
    case 'w':
        if (y > 0)
            y--;

        break;

    case 'a':
        if (x > 0)
            x--;

        break;

    case 's':
        if (y < size)
            y++;

        break;

    case 'd':
        if (x < size)
            x++;

        break;
    case 'j':
        if (!board[y][x])
        {
            board[y][x] = player + 1;
            player ^= 1;
        }
    }
}
void Print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((j == x) && (i == y))
                printf("╋");
            else if (board[i][j] == 2)
                printf("●");
            else if (board[i][j] == 1)
                printf("○");
            else if (i == 0 && j == 0)
                printf("╔");
            else if (i == 0 && (j == size - 1))
                printf("╗");
            else if ((i == size - 1) && j == 0)
                printf("╚");
            else if ((i == size - 1) && (j == size - 1))
                printf("╝");
            else if (i == 0)
                printf("╦");
            else if (i == size - 1)
                printf("╩");
            else if (j == 0)
                printf("╠");
            else if (j == size - 1)
                printf("╣");
            else
                printf("┼");
        }
        printf("\n");
    }
}
int main()
{
    COORD pos = {0, 0};

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    system("mode con lines=31 cols=101");
    system("color E0");
    memset(board, 0, sizeof(board));
    Print();
    while (1)
    {
        Drop();
        PanDing();
        SetConsoleCursorPosition(hOut, pos);
        Print();
    }

    return 0;
}