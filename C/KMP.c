/**
 * @file KMP.c
 * @author your name (you@domain.com)
 * @brief 字符串的模式匹配 
 * @version 0.1
 * @date 2022-07-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int KMP(char *str, char *pattern, int index);
int brute(char *str, char *pattern, int index);

int main(void)
{
    char str[256], pattern[256];
    printf("Please enter a string: ");
    scanf("%s", str);
    char ch;
    while((ch = getchar()) != '\n');
    printf("Please enter a pattern string: ");
    scanf("%s", pattern);
    printf("The KMP algorithm: index = %d\n", KMP(str, pattern, 0));
    printf("The brute algorithm: index = %d\n", brute(str, pattern, 0));
    getchar();
    return 0;
}

// 生成next数组（最长公共前后缀数组），时间复杂度O(m)
int *getNext(char *pattern)
{
    int *next = (int*)malloc(strlen(pattern) * sizeof(int));
    next[0] = 0;
    int i = 1, j = 0;
    while(i < strlen(pattern))
    {
        if(pattern[i] == pattern[j])
        {
            next[i++] = ++j;
        }
        else if(j == 0)
        {
            next[i++] = 0;
        }
        else
        {
            j = next[j - 1];
        }
    }
    return next;
}

// KMP算法匹配字符串子串，时间复杂度O(m+n)
int KMP(char *str, char *pattern, int pos)
{
    int *next = getNext(pattern);
    int i = pos, j = 0;  // j指向pattern首元素
    while(i < strlen(str) && j < strlen(pattern))
    {
        if(str[i] == pattern[j])
        {
            i++; j++;
        }
        else if(j == 0) // 子串的首字母匹配失败
        {
            i++;
        }
        else 
        {
            j = next[j - 1];
        }
    }
    free(next); // 释放内存
    if(j == strlen(pattern)) return i - j;
    return -1;
}

// 暴力匹配算法，时间复杂度O(m*n)
int brute(char *str, char *pattern, int pos)
{
    int i = pos, j = 0;
    while(i < strlen(str) && j < strlen(pattern))
    {
        if(str[i] == pattern[j])
        {
            i++; j++;
        }
        else
        {
            i = i - j + 1; // 将index定位到基点下一位
            j = 0; // 子串重新开始进行匹配
        }
    }
    if(j == strlen(pattern)) return i - j;
    return -1; 
}