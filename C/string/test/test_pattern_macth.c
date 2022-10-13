//
// Created by Anvei on 2022/10/8.
//
//  KMP算法以及暴力算法测试

#include "../utils/strutils.h"
#include <stdio.h>

int main(void)
{
    char target[] = "ababacababababcacab";
    char pattern[] = "ababc";
    int bruteRes = brute_force_match(target, pattern, 0);
    int kmpRes = kmp_match(target, pattern, 0);
    printf("bruteRes = %d, kmpRes = %d\n", bruteRes, kmpRes);
    return 0;
}
