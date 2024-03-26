#include <iostream>
#include <random>
#include <windows.h>
#include <ctime>
#define size 26
using namespace std;
enum colors
{
    black,
    blue,
    green,
    lake,
    red,
    purple,
    yellow,
    white,
    grey,
    lblue,
    lgreen,
    cyan,
    lred,
    lpurple,
    lyellow,
    lwhite,
};

/* 更改控制台文字颜色 */
void color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x % 16);
}

struct block
{
    int color;
    int num;
};

int main()
{
    random_device rd;
    srand((unsigned)time(NULL));
    mt19937 gen(rand()+rd()+(unsigned)time(NULL));
    uniform_int_distribution<> dis(0, 1);
    block map[size][size];

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            map[i][j].color = dis(gen);
            map[i][j].num=8;
        }
    }

    for (size_t i = 1; i < size-1; i++)
    {
        for (size_t j = 1; j <size-1; j++)
        {
            if(map[i-1][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i-1][j].color==1)
            {
                map[i][j].num--;
            }
            if(map[i-1][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j].num<=3)
            {
                map[i][j].color=1;
            }
            if(map[i][j].num>=5)
            {
                map[i][j].color=0;
            }
        }
    }    
   
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            map[i][j].num=8;
        }
    }
   
    for (size_t i = 1; i < size-1; i++)
    {
        for (size_t j = 1; j <size-1; j++)
        {
            if(map[i-1][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i-1][j].color==1)
            {
                map[i][j].num--;
            }
            if(map[i-1][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j].num<=3)
            {
                map[i][j].color=1;
            }
            if(map[i][j].num>=5)
            {
                map[i][j].color=0;
            }
        }
    }
    
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            map[i][j].num=8;
        }
    }
    
    for (size_t i = 1; i < size-1; i++)
    {
        for (size_t j = 1; j <size-1; j++)
        {
            if(map[i-1][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i-1][j].color==1)
            {
                map[i][j].num--;
            }
            if(map[i-1][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j-1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j].color==1)
            {
                map[i][j].num--;
            }
            if(map[i+1][j+1].color==1)
            {
                map[i][j].num--;
            }
            if(map[i][j].num<=3)
            {
                map[i][j].color=1;
            }
            if(map[i][j].num>=5)
            {
                map[i][j].color=0;
            }
        }
    }    
    
    for (size_t i = 1; i < size-1; i++)
    {
        for (size_t j = 1; j < size-1; j++)
        {
            if(map[i][j].color)
            {
                color(lgreen);
            }
            else
            {
                color(green);
            }
            printf("█");
        }
        printf("\n");
    }
    return 0;
}
