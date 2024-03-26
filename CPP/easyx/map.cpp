#include <iostream>
#include <random>
#include <graphics.h>
#include <ctime>
#include <algorithm>
#define size 501
using namespace std;

struct block
{
    unsigned char num;
    bool color;
} map[size][size];

void wash()
{
    block *p = &map[0][0];
    for (size_t i = 0; i < size * size; i++)
    {
        (p++)->num = 8;
    }

    for (size_t i = 1; i < size - 1; i++)
    {
        for (size_t j = 1; j < size - 1; j++)
        {
            if (map[i - 1][j - 1].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i - 1][j].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i - 1][j + 1].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i][j - 1].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i][j + 1].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i + 1][j - 1].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i + 1][j].color == 1)
            {
                map[i][j].num--;
            }
            if (map[i + 1][j + 1].color == 1)
            {
                map[i][j].num--;
            }

            if (map[i][j].num <= 3)
            {
                map[i][j].color = 1;
            }
            if (map[i][j].num >= 5)
            {
                map[i][j].color = 0;
            }
        }
    }
}

int main()
{
    random_device rd;
    srand((unsigned)time(NULL));
    mt19937 gen(rand() + rd() + (unsigned)time(NULL));
    uniform_int_distribution<> dis(0, 1);
    block *p = &map[0][0];

    initgraph(500, 500);
    for (size_t i = 0; i < size * size; i++)
    {
        (p++)->color = dis(gen);
    }

    for (size_t i = 1; i < size - 1; i++)
    {
        for (size_t j = 1; j < size - 1; j++)
        {
            if (map[i][j].color)
            {
                putpixel(i - 1, j - 1, 0xFFFFFF);
            }
            else
            {
                putpixel(i - 1, j - 1, 0x000000);
            }
        }
    }
    system("pause");
    return 0;
}
