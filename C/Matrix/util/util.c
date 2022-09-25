//
// Created by Anvei on 2022/9/24.
//

#include "util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

bool isPrime(int num)
{
    for (int i = 2; i < sqrt(num); i++)         // 对穷举算法进行优化，时间复杂度O(sqrt(n))
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

// 欧几里得最大公约数算法
int gcd(int num1, int num2)
{
    if (num1 % num2 == 0)
        return num2;
    return gcd(num2, num1 % num2);
}

// 对n个数求最大公约数
int gcd_n(int len, int list[])
{
    if (len <= 0)
    {
        printf("time: %s, file: %s, line: %d ERROR: 参数len必须大于0!\n", __TIME__, __FILE__, __LINE__);
        exit(-1);
    }
    if (len == 1)
        return list[0];
    int res[len / 2], count = 0;
    for (int i = 0; i < len - 1; i = i + 2)
        res[count++] = gcd(list[i], list[i + 1]);
    if (len % 2)
        res[count] = list[len - 1];
    return gcd_n(len / 2, res);
}

// 求最小公倍数
int lcm(int num1, int num2)
{
    num1 = abs(num1);
    num2 = abs(num2);
    int lcmNum = num1 > num2 ? num1 : num2;
    while(true)
    {
        if (lcmNum % num1 == 0 && lcmNum % num2 == 0)
            return lcmNum;
        lcmNum++;
    }
}

// 对n个数求最小公倍数
int lcm_n(int len, int list[])
{
    if (len <= 0)
    {
        printf("time: %s, file: %s, line: %d ERROR: 参数len必须大于0!\n", __TIME__, __FILE__, __LINE__);
        exit(-1);
    }
    if (len == 1)
        return list[0];
    int res[len / 2], count = 0;
    for (int i = 0; i < len - 1; i = i + 2)
        res[count++] = lcm(list[i], list[i + 1]);
    if (len % 2)
        res[count] = list[len - 1];
    return lcm_n(len / 2, res);
}
