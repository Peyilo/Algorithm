/*
最大公约数求解
*/

#include <stdio.h>
#include "algorithm.h"
#define NUM1 21133
#define NUM2 322


// Test
int main(void)
{   
    printf("gcd1 = %d gcd2 = %d EuclidGCD = %d", gcd1(NUM1, NUM2), gcd2(NUM2, NUM1), EuclidGCD(NUM2, NUM1));
    return 0;
}

int gcd1(int a, int b)
{
    int result;
    for (int i = 1; i < a && i < b; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            result = i;
        }
    }
    return result;
}

int gcd2(int a, int b)
{
    int result;
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        for (int i = 1; i < b/2; i++)
        {
            if (a % i == 0 && b % i == 0)
            {
                result = i;
            }
        }
        return result;
    }
}

// Euclid公约数算法，时间复杂度O(log2n)
int EuclidGCD(int a, int b)
{
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        return EuclidGCD(b, a % b);
    }
}