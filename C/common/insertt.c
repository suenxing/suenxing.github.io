// 数组插入一个元素
#include <stdio.h>
#include <stdlib.h>

void insert(int *arr, int lenth, int num)
{
    for (int i = 0; i < lenth; i++)
    {
        if (arr[i] > num)
        {
            for (int j = lenth - 1; j > i; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[i] = num;
            break;
        }
    }
}
int main()
{
    int arr[11] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, -1};
    insert(arr, 11, 5);
    for (int i = 0; i < 11; i++)
    {
        printf("%d ", arr[i]);
    }
    system("pause");
    return 0;
}