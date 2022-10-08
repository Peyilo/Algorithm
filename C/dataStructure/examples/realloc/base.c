//
// Created by Anvei on 2022/10/7.
//
#include <stdio.h>
#include <malloc.h>

// realloc()函数会返回新分配的地址，并且会原先的数据复制到新地址中
// 如果重新分配的空间小于原先的，会按照顺序进行截断数据
int main(void)
{
    int *arr = malloc(sizeof(int) * 20);
    for (int i = 0; i < 20; i++)
    {
        arr[i] = i;
    }
    printf("start: %p, end: %p\n", arr, arr + 20);
    int *temp = malloc(sizeof(int) * 10);
    arr = realloc(arr, sizeof(int) * 10);
    printf("start: %p, end: %p\n", arr, arr + 30);
    for (int i = 0; i < 10; i++)
    {
        printf("%2d ", arr[i]);
        if ((i + 1) % 10 == 0) putchar('\n');
    }
    return 0;
}
