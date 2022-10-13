//
// Created by Anvei on 2022/10/9.
//

#include "String.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define STRING_INCREMENT_SIZE 10

/**
 * 为字符串指定下标设置一个字符
 * @param pstr
 * @param index
 * @param ch
 * @return 设置成功则返回true
 */
bool str_set(String *pstr, int index, char ch)
{
    // 处理index错误情形
    if (pstr->len < index) return false;
    // 处理内存不够的情形
    if (pstr->size == index)
    {
        char *temp = realloc(pstr->str, sizeof(char) * (pstr->size + STRING_INCREMENT_SIZE + 1));
        if (!temp) return false;
        pstr->str = temp;
        pstr->size += STRING_INCREMENT_SIZE;
    }
    if (pstr->len == index)
        *(pstr->str + index + 1) = '\0';            // 保证字符串最后一个字符的下一位是'\0'
    *(pstr->str + index) = ch;
    pstr->len++;
    return true;
}

/**
 * 使用char *类型给字符串进行初始化
 * @param pstr
 * @param init_str
 * @return
 */
bool str_init(String *pstr, const char *init_str)
{
    int len = (int) strlen(init_str);
    char *temp = malloc(sizeof(char) * (len + 1));
    if (!temp) return false;
    pstr->len = len;
    pstr->size = len;
    pstr->str = temp;
    for (int i = 0; i < len; i++)
        *(temp + i) = *init_str++;
    *(temp + len) = '\0';
    return true;
}

/**
 * 指定字符串长度进行初始化
 * @param pstr
 * @param len
 * @return
 */
bool str_init_by_size(String *pstr, int len)
{
    char *temp = malloc(sizeof(char) * (len + 1));
    if (!temp) return false;
    pstr->len = 0;
    pstr->size = len;
    pstr->str = temp;
    *temp = '\0';
    return true;
}

/**
 * 销毁一个字符串
 * @param str
 */
void str_destory(String str)
{
    free(str.str);
}

/**
 * 获取字符拆指定下标的字符
 * @param str
 * @param index
 * @return
 */
char str_get(String str, int index)
{
    if (index >= str.len) exit(__LINE__);
    return *(str.str + index);
}

/**
 *  打印字符串
 * @param str
 */
void str_putstring(String str)
{
    for (int i = 0; i < str.len; i++)
        putchar(str_get(str, i));
}
