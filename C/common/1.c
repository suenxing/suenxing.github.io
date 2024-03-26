#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int arr[5], map[4][4] = {
                    {0, 1, 2, 3}, {1, 1, 4, 5}, {0, 0, 0, 0}, {9, 9, 9, 9}};
    memcpy(arr, map[1], sizeof(arr));
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    system("pause");
    return 0;
}