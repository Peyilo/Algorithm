/*
排序算法,以下排序算法都是升序排序
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithm.h"
#define LENGTH 10

// 定义枚举，用于表示布尔变量
enum bool{false, true};

// 测试
int main(void)
{
    int size, *array;
    printf("请输入需要生成的随机数数组大小：");
    scanf("%d", &size);
    array = myRand(size);
    printf("排序之前：\n");
    myPrint(array, size);
    merge_sort(array, size);
    printf("排序之后：\n");
    myPrint(array, size);

    free(array);
    return 0;
}

// 选择排序
void selectSort(int *array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int minNum = array[i];
        int minIndex = i;
        for (int j = i + 1; j < length; j++)
        {
            if (minNum > array[j])
            {
                minNum = array[j];
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(array + i, array + minIndex);
        }
    }
}

// 冒泡排序
void bubbleSort(int *array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int flag = 0;
        for (int j = 0; j < length - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                swap(array + j, array + j + 1);
                flag = 1;
            }
        }
        if(!flag) return;
    }
}

// 插入排序
void insertSort(int *array, int length)
{
    for (int i = 1; i < length; i++)
    {
        int val = array[i];
        int position = i;
        while(position > 0 && val < array[position - 1])
        {
            array[position--] = array[position - 1];
        }
        if(position != i)
        {
            array[position] = val;
        }
    }
}

// 快速排序
void quickSort(int *array, int length)
{
    quick(array, 0, length - 1);
}

void quick(int *array, int lowIndex, int highIndex)
{
    if(lowIndex < highIndex)
    {
        int partIndex = partition(array, lowIndex, highIndex);
        quick(array, lowIndex, partIndex - 1);
        quick(array, partIndex + 1, highIndex);
    }
}
// 分割数组，返回分界下标
int partition(int *array, int lowIndex, int highIndex)
{
    int pivot = array[lowIndex]; // 选定中心点
    while(lowIndex < highIndex)
    {
        while(lowIndex < highIndex && pivot <= array[highIndex])
        {
            highIndex--;
        }
        if(lowIndex < highIndex) 
        {
            array[lowIndex++] = array[highIndex]; 
        }
        while(lowIndex < highIndex && pivot >= array[lowIndex])
        {
            lowIndex++;
        }
        if(lowIndex < highIndex) 
        {
            array[highIndex++] = array[lowIndex];
        }
    }
    array[lowIndex] = pivot;
    return lowIndex;
}

// 希尔排序
void shellSort(int *array, int length)
{
    int interval = 1;
    while(interval < length / 3)
    {
        interval = interval * 3 + 1;
    }
    while(interval > 0)
    {
        for (int i = interval; i < length; i++)
        {
            int val = array[i];
            int position = i;
            while(position > interval - 1 && val < array[position - interval])
            {
                array[position] = array[position - interval];
                position -= interval;
            }
            if(position != i)
            {
                array[position] = val;
            }
        }
        interval = (interval - 1) / 3;
    }
}

// 归并排序
void mergeSort(int *array, int length)
{
    int temp[length];
    merge(array, temp, 0, length - 1);
}

void merge(int *array, int *temp, int lowIndex, int highIndex)
{
    if (lowIndex >= highIndex) return;
    int length = highIndex - lowIndex - 1, mid = (length >> 1) + lowIndex;
    int start1 = lowIndex, end1 = mid;
    int start2 = mid + 1, end2 = highIndex;
    merge(array, temp, start1, end1);
    merge(array, temp, start2, end2);
    int index = lowIndex;
    // 归并
    while(start1 <= end1 && start2 <= end2)
    {
        temp[index++] = array[start1] < array[start2] ? array[start1++] : array[start2++];
    }
    while(start1 <= end1)
    {
        temp[index++] = array[start1++];
    }
    while(start2 <= end2)
    {
        temp[index++] = array[start2++];
    }
    // 将temp内的数据复制回array
    for(index = lowIndex; index <= highIndex; index++)
    {
        array[index] = array[index];
    }
}

void merge_sort_recursive(int arr[], int reg[], int start, int end) {
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1)
        reg[k++] = arr[start1++];
    while (start2 <= end2)
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = reg[k];
}
void merge_sort(int arr[], const int len) {
    int reg[len];
    merge_sort_recursive(arr, reg, 0, len - 1);
}

// 复制数组
void arrayCopy(int *srcArray, int index1, int *desArray, int index2, int length)
{
    for(int i = index1, j = index2, count = 0; count < length; i++, j++, count++)
    {
        desArray[j] = srcArray[i];
    }
}
// 使用位操作实现数字交换
void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

// 打印数组，需要指定长度和数组
void myPrint(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%4d ", array[i]);
    }
    printf("\n");
}

// 生成指定长度的随机数数组
int * myRand(int length)
{
    if(length > 100)
    {
        printf("请输入一个不大于100的正数！");
        exit(-1);
    }
    int *array = (int*)calloc(length, sizeof(int));
    if (array == NULL)
    {
        exit(-1);
    }
    else
    {
        for(int i = 0; i< length; i++)
        {
        srand(((unsigned)time(NULL) + 21)* i * 101);
        array[i] = rand() % 10000;
        }
        return array;
    }
}