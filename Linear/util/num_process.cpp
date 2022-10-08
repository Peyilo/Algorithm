//
// Created by Anvei on 2022/10/1.
//

#include "num_process.h"
#include <cmath>
#include <cassert>

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
int gcd(int len, int *list)
{
    assert(len >= 1);
    if (len == 1)
        return list[0];
    int res[len / 2], count = 0;
    for (int i = 0; i < len - 1; i = i + 2)
        res[count++] = gcd(list[i], list[i + 1]);
    if (len % 2)
        res[count] = list[len - 1];
    return gcd(len / 2, res);
}

int gcd(vector<int> vec)
{
    auto len = vec.size();
    assert(len >= 1);
    if (len == 1)
        return vec[0];
    vector<int> res(len / 2);
    int count = 0;
    for (int i = 0; i < len - 1; i = i + 2)
        res[count++] = gcd(vec[i], vec[i + 1]);
    if (len % 2)
        res[count] = vec[len - 1];
    return gcd(res);
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
int lcm(int len, int *list)
{
    assert(len >= 1);
    if (len == 1)
        return list[0];
    int res[len / 2], count = 0;
    for (int i = 0; i < len - 1; i = i + 2)
        res[count++] = lcm(list[i], list[i + 1]);
    if (len % 2)
        res[count] = list[len - 1];
    return lcm(len / 2, res);
}

int lcm(vector<int> vec)
{
    auto len = vec.size();
    assert(len >= 1);
    if (len == 1)
        return vec[0];
    vector<int> res(len / 2);
    int count = 0;
    for (int i = 0; i < len - 1; i = i + 2)
        res[count++] = gcd(vec[i], vec[i + 1]);
    if (len % 2)
        res[count] = vec[len - 1];
    return lcm(res);
}