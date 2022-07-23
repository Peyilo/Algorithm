#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *getNext(char *pattern);
int KMP(char *str, char *pattern);
int brute(char *str, char *pattern);
int brute_(char *str, char *pattern, int index);

int main(void)
{
    char str[256], pattern[256];
    printf("Please enter a string: ");
    scanf("%s", str);
    char ch;
    while((ch = getchar()) != '\n');
    printf("Please enter a pattern string: ");
    scanf("%s", pattern);
    printf("The KMP algorithm: index = %d\n", KMP(str, pattern));
    printf("The brute algorithm: index = %d\n", brute(str, pattern));
    getchar();
    return 0;
}

// 生成next数组（最长公共前后缀数组）
int *getNext(char *pattern)
{
    int *next = (int*)malloc(strlen(pattern) * sizeof(int));
    next[0] = 0;
    int prefix_len = 0, i = 1;
    while(i < strlen(pattern))
    {
        if(pattern[prefix_len] == pattern[i])
        {
            prefix_len++;
            next[i++] = prefix_len;
        }
        else
        {
            if(prefix_len == 0)
            {
                next[i++] = 0;
            }
            else
            {
                prefix_len = next[prefix_len - 1];
            }
        }
    } 
    return next;
}

// KMP算法匹配字符串子串
int KMP(char *str, char *pattern)
{
    int index = -1; // 如果匹配失败，则返回-1
    int *next = getNext(pattern);
    int i = 0, j = 0;  // i指向str首元素，j指向pattern首元素
    while(i < strlen(str))
    {
        if(str[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if(j > 0)
        {
            j = next[j - 1];
        }
        else // 子串的首字母匹配失败
        {
            i++;
        }
        if (j == strlen(pattern)) // 表示已经完全匹配成功
        {
            index = i - j;
            break;
        }
    }
    free(next); // 释放内存
    return index;
}

int brute(char *str, char *pattern)
{
    return brute_(str, pattern, 0);
}
// 暴力匹配算法
int brute_(char *str, char *pattern, int index)
{
    int i = 0;
    while(index < strlen(str) && i < strlen(pattern))
    {
        if(str[index] == pattern[i])
        {
            index++;
            i++;
        }
        else
        {
            i = 1;
            index = index - i + 1;
        }
    }
    if(i == strlen(pattern)) return index - i;
    return -1; 
}