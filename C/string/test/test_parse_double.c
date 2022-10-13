//
// Created by Anvei on 2022/10/12.
//

#include "../utils/strutils.h"
#include <stdio.h>

/**
 * 解析
 * @param expr
 * @return
 */

int main(void)
{
    const char *expr = "-12.320";
    printf("parse result: %f\n", parse_double(expr));
    return 0;
}