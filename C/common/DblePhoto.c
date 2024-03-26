#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    fflush(stdin);
    char p1[n][m], p2[n * 2][m * 2];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%c", &p1[i][j]);
        }
        fflush(stdin);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            p2[i * 2 + 1][j * 2] =
                p2[i * 2 + 1][j * 2 + 1] =
                    p2[i * 2][j * 2 + 1] =
                        p2[i * 2][j * 2] =
                            p1[i][j];
        }
    }

    for (i = 0; i < n * 2; i++)
    {
        for (j = 0; j < m * 2; j++)
        {
            printf("%c", p2[i][j]);
        }
        printf("\n");
    }
    system("pause");
    return 0;
}