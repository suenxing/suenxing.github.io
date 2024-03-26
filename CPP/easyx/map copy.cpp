#include <iostream>
#include <random>
#include <graphics.h>
#include <ctime>
#include <algorithm>
#define size 502
using namespace std;

double map[size][size];

void wash()
{
    printf("Wash Begining(0)...\n");
    // →
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size - 1; j++)
        {
            map[i][j] = (map[i - 1][j] + map[i][j - 1] + map[i][j + 1] + map[i + 1][j]) / 4;
        }
    }
    /*
        printf("Wash Begining(1)...\n");
        // ←
        for (int i = size - 1; i > 1; i--)
        {
            for (int j = size - 1; j > 1; j--)
            {
                map[i][j] = (map[i][j] + map[i][j - 1]) / 2;
            }
        }
        // ↓
        printf("Wash Begining(2)...\n");
        for (int i = 1; i < size - 1; i++)
        {
            for (int j = 1; j < size - 1; j++)
            {
                map[i][j] = (map[i][j] + map[i + 1][j]) / 2;
            }
        }
        // ↑
        printf("Wash Begining(3)...\n");
        for (int i = size - 1; i > 1; i--)
        {
            for (int j = size - 1; j > 1; j--)
            {
                map[i][j] = (map[i][j] + map[i - 1][j]) / 2;
            }
        } */
    printf("Wash Finished\n");
}

int main()
{
    srand((unsigned)time(NULL));
    mt19937 gen(rand() + (unsigned)time(NULL));
    uniform_real_distribution<> dis(0, 1);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            map[i][j] = dis(gen);
        }
    }

    initgraph(size - 2, size - 2);
    BeginBatchDraw();
    for (int i = 0; i < 512; i++)
    {
        wash();
        for (int i = 1; i < size - 1; i++)
        {
            for (int j = 1; j < size - 1; j++)
            {
                putpixel(i - 1, j - 1, HSVtoRGB(0, 0, map[i][j]));
            }
        }
        FlushBatchDraw();
    }

    system("pause");
    EndBatchDraw();
    return 0;
}
