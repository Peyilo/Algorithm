//
// Created by Anvei on 2022/10/8.
//
// 模式匹配

#include <string.h>
#include <malloc.h>

/**
 * 字符串匹配的暴力实现，时间复杂度O(m * n)
 * @param arr 目标字符串
 * @param pattern 将要匹配的子串
 * @param pos 从目标字符串下标pos开始进行匹配
 * @return 返回匹配成功的子串的首个字符的下标
 */
int brute_force_match(const char *target, const char *pattern, int pos)
{
    int i = pos, j = 0;
    int len1 = (int) strlen(target), len2 = (int) strlen(pattern);
    while (i < len1 && j < len2)
    {
        if (target[i] == pattern[j])        // 如果匹配成功下标移动一位
            i++, j++;
        else
        {
            i = i - j + 1;                  // 从下一个字符开始匹配
            j = 0;
        }
    }
    if (j == len2)
        return i - j;           // 返回匹配成功时首字符下标
    return -1;                  // 匹配失败
}

/**
 * 获取最长公共前后缀数组
 * @param str
 * @return
 */
static int *get_next(const char *str)
{
    int *next = malloc(sizeof(int) * strlen(str));
    next[0] = 0;        // 当只有一个字符时，定义最长公共前后缀长度为0
    int i = 1, j = 0;
    int len = (int) strlen(str);
    while (i < len)     // 开始计算从下标1开始的next数组
    {
        if (str[i] == str[j])
            next[i++] = ++j;
        else if (j == 0)        // 首字母就匹配失败
            next[i++] = 0;
        else
            j = next[j - 1];
    }
    return next;
}

// KMP算法匹配子串的实现，时间复杂度O(m + n)，
// 当m、n比较小的时候，与暴力算法运行时间相近
int kmp_match(const char *target, const char *pattern, int pos)
{
    int *next = get_next(pattern);
    int len1 = (int) strlen(target), len2 = (int) strlen(pattern);
    int i = pos, j = 0;
    while (i < len1 && j < len2)
    {
        if (target[i] == pattern[j])        // 匹配成功
            i++, j++;
        else if (j == 0)                    // 处理j = 0时，没有前一位的问题
            i++;
        else
            j = next[j - 1];                // 根据前一位的next数组值进行移动子串
    }
    free(next);
    if (j == len2)
        return i - j;
    return -1;
}