//
// Created by Anvei on 2022/10/10.
//
#include <stdio.h>
#include "../utils/strutils.h"

int main(void)
{
    printf("请输入一个表达式：");
    char expr[100] = {0};
    gets(expr);
    printf("result = %f\n", rpn_eval(expr));
    return 0;
}
