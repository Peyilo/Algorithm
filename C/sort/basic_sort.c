//
// Created by Anvei on 2022/10/8.
//
// 提供基本排序算法的实现

#include "sortutils.h"

// 选择排序的实现
void select_sort(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int minval = arr[i];
        int minIndex = i;
        for (int j = i + 1; j < len; j++)
        {
            if (minval > arr[j])
            {
                minval = arr[j];
                minIndex = j;
            }
        }
        if (minIndex != i)
            swap(arr + i, arr + minIndex);
    }
}

// 冒泡排序的实现
void bubble_sort(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int flag = 1;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                flag = 0;
                swap(arr + j, arr + j + 1);
            }
        }
        if (flag) break;
    }
}

// 插入排序的实现
void insert_sort(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        int val = arr[i];
        int index = i;
        while (index > 0 && arr[index - 1] > val)
        {
            arr[index] = arr[index - 1];
            index--;
        }
        if (index != i) arr[index] = val;
    }
}

/**
 * 归并数组指定区域的元素
 * @param arr
 * @param temp 临时数组用于保证多次递归过程中使用同一个数组，以节省空间
 * @param low
 * @param high
 */
void merge(int *arr, int *temp, int low, int high)
{
    if (low >= high) return;
    int mid = (high + low) / 2;
    int low1 = low,
            high1 = mid,
            low2 = mid + 1,
            high2 = high;
    merge(arr, temp, low1, high1);
    merge(arr, temp, low2, high2);

    // 将arr数组的指定两段元素进行归并，归并结果存储在数组temp中
    int index = low1, index1 = low1, index2 = low2;
    while (index1 <= high1 && index2 <= high2)
        temp[index++] = arr[index1] < arr[index2] ? arr[index1++] : arr[index2++];
    while (index1 <= high1)
        temp[index++] = arr[index1++];
    while (index2 <= high2)
        temp[index++] = arr[index2++];

    // 将数组temp中的元素复制到arr中去
    while (low1 <= high2)
    {
        arr[low1] = temp[low1];
        low1++;
    }
}

// 归并排序
void merge_sort(int *arr, int len)
{
    int temp[len];
    merge(arr, temp, 0, len - 1);
}

/**
 * 保证选取的pivot左侧全小于pivot，右侧全部大于pivot，并返回pivot的下标
 * @param arr
 * @param low
 * @param high
 * @return
 */
int partition(int *arr, int low, int high)
{
    int pivot = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] > pivot)
        {
            high--;
        }
        if (low < high)
        {
            swap(arr + high, arr + low);
            low++;
        }
        while (low < high && arr[low] < pivot)
        {
            low++;
        }
        if (low < high)
        {
            swap(arr + low, arr + high);
            high--;
        }
    }
    return low;
}

// 对数组指定下标之间的元素快速排序
void quick(int *arr, int low, int high)
{
    if (low >= high) return;
    int part = partition(arr, low, high);
    quick(arr, low, part - 1);
    quick(arr, part + 1, high);
}

// 快速排序的实现
void quick_sort(int *arr, int len)
{
    quick(arr, 0, len - 1);
}

// 希尔排序的实现，本质是优化过的插入排序
void shell_sort(int *arr, int len)
{
    int interval = 1;           // 调整间隔
    while (interval < len / 3)
    {
        interval = interval * 3 + 1;
    }
    while (interval > 0)
    {
        for (int i = interval; i < len; i++)
        {
            int val = arr[i];
            int index = i;
            while (index > interval -1 && arr[index - interval] > val)
            {
                arr[index] = arr[index - interval];
                index -= interval;
            }
            if (index != i) arr[index] = val;
        }
        interval = (interval - 1) / 3;
    }
}
