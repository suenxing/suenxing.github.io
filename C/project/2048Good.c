#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define N 4

int grid[N][N] = {0};
int D = 0;
int M = 2048;

// 显示
void showdata()
{
    int i, j;
    system("CLS");
    for (i = 0; i < N + 2; i++)
    {
        printf("%5c", '+');
    }
    printf("\n\n");
    for (i = 0; i < N; i++)
    {
        printf("%5c", '+');
        for (j = 0; j < N; j++)
            if (grid[i][j] != 0)
            {
                printf("%5d", grid[i][j]);
            }
            else
            {
                printf("%5c", ' ');
            }
        printf("%5c", '+');
        printf("\n\n");
    }
    for (i = 0; i < N + 2; i++)
    {
        printf("%5c", '+');
    }
    printf("\n");
}
// 判断是否有空位
int isNotFull()
{
    int i, j, k = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (grid[i][j] == 0)
            {
                k = 1;
                break;
            }
    return k;
}
// 随机数字
void randomdata()
{
    int r, c, x;
    x = rand() % 2 * 2 + 2;
    do
    {
        r = rand() % N;
        c = rand() % N;
    } while (grid[r][c] != 0);
    grid[r][c] = x;
}
// 获取最大值
int getMax()
{
    int i, j, max = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (max < grid[i][j])
            {
                max = grid[i][j];
            }
    return max;
}
// 移动相加,返回1表示有移动，返回0表示无移动
int add()
{
    int i, j, cr, w, F = 0;
    if (D == 1) // top
    {
        for (i = 1; i < N; i++)
            for (j = 0; j < N; j++)
            {
                cr = i;
                w = 0; // 0:未合并  1：合并过
                while (cr >= 1 && grid[cr][j] != 0)
                {
                    if (grid[cr - 1][j] == 0) // 上方有空位，上移
                    {
                        grid[cr - 1][j] = grid[cr][j];
                        grid[cr][j] = 0;
                        F = 1;
                    }
                    else // 上方无空位
                    {
                        if (grid[cr - 1][j] == grid[cr][j] && w == 0) // 相等，相加
                        {
                            grid[cr - 1][j] = grid[cr - 1][j] * 2;
                            grid[cr][j] = 0;
                            w = 1;
                            F = 1;
                        }
                        else // 不等
                        {
                            break;
                        }
                    }
                    cr--;
                }
            }
    }
    if (D == 2) // down
    {
        for (i = N - 2; i >= 0; i--)
            for (j = 0; j < N; j++)
            {
                cr = i;
                w = 0;
                while (cr <= N - 2 && grid[cr][j] != 0)
                {
                    if (grid[cr + 1][j] == 0) // 下方有空位，下移
                    {
                        grid[cr + 1][j] = grid[cr][j];
                        grid[cr][j] = 0;
                        F = 1;
                    }
                    else // 下方无空位
                    {
                        if (grid[cr + 1][j] == grid[cr][j] && w == 0) // 相等，相加
                        {
                            grid[cr + 1][j] = grid[cr + 1][j] * 2;
                            grid[cr][j] = 0;
                            w = 1;
                            F = 1;
                        }
                        else // 不等
                        {
                            break;
                        }
                    }
                    cr++;
                }
            }
    }
    if (D == 3) // left
    {
        for (i = 0; i < N; i++)
            for (j = 1; j < N; j++)
            {
                cr = j;
                w = 0;
                while (cr >= 1 && grid[i][cr] != 0)
                {
                    if (grid[i][cr - 1] == 0) // 左方有空位，左移
                    {
                        grid[i][cr - 1] = grid[i][cr];
                        grid[i][cr] = 0;
                        F = 1;
                    }
                    else // 左方无空位
                    {
                        if (grid[i][cr - 1] == grid[i][cr] && w == 0) // 相等，相加
                        {
                            grid[i][cr - 1] = grid[i][cr - 1] * 2;
                            grid[i][cr] = 0;
                            w = 1;
                            F = 1;
                        }
                        else // 不等
                        {
                            break;
                        }
                    }
                    cr--;
                }
            }
    }
    if (D == 4) // right
    {
        for (i = 0; i < N; i++)
            for (j = N - 2; j >= 0; j--)
            {
                cr = j;
                w = 0;
                while (cr <= N - 2 && grid[i][cr] != 0)
                {
                    if (grid[i][cr + 1] == 0) // 右方有空位，右移
                    {
                        grid[i][cr + 1] = grid[i][cr];
                        grid[i][cr] = 0;
                        F = 1;
                    }
                    else // 右方无空位
                    {
                        if (grid[i][cr + 1] == grid[i][cr] && w == 0) // 相等，相加
                        {
                            grid[i][cr + 1] = grid[i][cr + 1] * 2;
                            grid[i][cr] = 0;
                            w = 1;
                            F = 1;
                        }
                        else // 不等
                        {
                            break;
                        }
                    }
                    cr++;
                }
            }
    }
    return F;
}

int getKey()
{
    int k = 0;
    char c = getch();
    if (c < 0) // c<0为特殊键，还要再读下一个字节判断为何键
    {
        c = getch();
        if (c == 72)
        {
            D = 1;
            k = 1;
        } // top
        if (c == 80)
        {
            D = 2;
            k = 1;
        } // down
        if (c == 75)
        {
            D = 3;
            k = 1;
        } // left
        if (c == 77)
        {
            D = 4;
            k = 1;
        } // right
    }
    return k;
}
// 在数字全满下，检查是否还有合并的可能，有则返回1；
int canAdd()
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N - 1; j++)
            if (grid[i][j] == grid[i][j + 1])
            {
                return 1;
            }

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < N - 1; i++)
        {
            if (grid[i][j] == grid[i + 1][j])
            {
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    int mov, isf;
    printf("请输入游戏要拼凑的最大数字，例如32，64，128，...，2048：");
    scanf("%d", &M);
    // 初次状态
    srand(time(NULL));
    randomdata(); // 随机第一个数
    randomdata(); // 随机第二个数
    showdata();
    do
    {
        if (getKey() == 0)
        {
            continue;
        }            // 不是上下左右键，重新读取键盘
        mov = add(); // 根据方向键合并相加,返回1表示有移动
        if (mov == 1)
        {
            showdata();
        }                  // 显示
        if (getMax() == M) // 判断是否胜利
        {
            printf("你赢了！\n");
            break;
        }
        isf = isNotFull(); // 返回1表示还有空位
        if (isf && mov)    // 有空位且有移动再随机
        {
            randomdata(); // 再随机
            showdata();   // 显示
        }
        if (!(isf && canAdd())) // 没有空间则游戏结束
        {
            break;
        }
    } while (1);
    return 0;
}
