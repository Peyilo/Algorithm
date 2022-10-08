//
// Created by Anvei on 2022/10/7.
//

#include "sortutils.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// 交换两个数
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 生成一个随机数组
void array_generate(int *arr, int len)
{
    srand(time(NULL));
    for (int i = 0; i < len; i++)
    {
        arr[i] =  rand() % 1000;
    }
}

// 打印数组
void array_print(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%3d ", arr[i]);
        if ((i + 1) % 10 == 0)
            putchar('\n');
    }
}