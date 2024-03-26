#include <stdio.h>
#include <stdlib.h>
#include <time.h> //生成随机数
void Sort1(int *arr)
{
    int i = 0, j = sizeof(*arr) / sizeof(arr[0]) - 1, temp;
    while (j > 0)
    {
        if (arr[i] > arr[j])
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        if (++i == j)
            --j, i = 0;
    }
}
void Sort2(int *arr, int left, int right) // 快速排序
{
    int i = left, j = right, temp;
    int pivot = arr[(left + right) / 2];

    while (i <= j)
    {
        // 从左到右找大于基准点的数
        while (arr[i] < pivot)
            i++;
        // 从右到左找小于基准点的数
        while (arr[j] > pivot)
            j--;
        // 如果i<j，互换
        if (i <= j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j)
    {
        Sort2(arr, left, j);
    }
    if (i < right)
    {
        Sort2(arr, i, right);
    }
}
int main()
{
    int arr[100];
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand() % 10;
    }
    Sort2(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", arr[i]);
    }
    system("pause");
    return 0;
}