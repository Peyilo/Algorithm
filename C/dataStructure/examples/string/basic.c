//
// Created by Anvei on 2022/10/10.
//
// 对字符串进行测试

#include "../../String.h"
#include <stdio.h>

int main(void)
{
    String str;
    str_init(&str, "Hello world!");
    printf("the length of the string: %d\n", str.len);
    printf("the size of the string: %d\n", str.size);
    str_putstring(str);
    String str2;
    str_init(&str2, "Anvei hhhhhhhhhhhhhhhhhhhhhhhvdghcvdschds#");
    str_destory(str);
    str_destory(str2);
    return 0;
}