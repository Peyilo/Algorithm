//
// Created by Anvei on 2022/9/24.
//
#include <stdio.h>
#include "../util/util.h"
#include <stdlib.h>

int main(void)
{
    int lcmNum = lcm(16, 72);
    printf("lcmNum = %d\n", lcmNum);
    printf("\x1b[32mHelloWorld\n\033[0m\n");
    getchar();
    return 0;
}
