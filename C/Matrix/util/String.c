//
// Created by Anvei on 2022/9/24.
//

#include "String.h"
#include <stdlib.h>
#include <stdio.h>

String * initString(char *str, int len)
{
    String *pString = malloc(sizeof(String));
    if (!pString) {         // 处理指针为空
        puts("字符串初始化失败");
        exit(-1);
    }
    pString->len = len;
    pString->str = malloc(sizeof(char) * len);
    char *temp = pString->str;
    while (*str != '\0')
    {
        *temp = *str;
        temp++;
        str++;
    }
    return pString;
}

void destroyString(String *pString)
{
    free(pString->str);
    free(pString);
}

void printString(String string)
{
    printf("%s", string.str);
}