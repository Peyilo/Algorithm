//
// Created by Anvei on 2022/9/24.
//
#include <stdio.h>
#include <stdlib.h>
#include "Fraction.h"
#include "util.h"

Fraction initFraction(int numerator, int denominator, Fraction *pFraction)
{
    if (denominator == 0) {
        printf("分子不能为0!\n");
        exit(-1);
    }
    pFraction->numerator = numerator;
    pFraction->denominator = denominator;
    simplify(pFraction);
    return *pFraction;
}

// 对fraction进行约分
void simplify(Fraction *pFraction)
{
    if (pFraction->numerator == 0) {
        pFraction->denominator = 1;
        return;
    }
    int gcdNum = gcd(pFraction->numerator, pFraction->denominator);
    if (gcdNum != 1) {
        pFraction->numerator /= gcdNum;
        pFraction->denominator /= gcdNum;
    }
    if (pFraction->denominator < 0)         // 不让分母带负号
    {
        pFraction->numerator = - pFraction->numerator;
        pFraction->denominator = - pFraction->denominator;
    }
}

Fraction addFraction(Fraction a, Fraction b, Fraction *result)
{
    result->numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result->denominator = a.denominator * b.denominator;
    simplify(result);
    return *result;
}

Fraction addNum(Fraction fraction, int num, Fraction *result)
{
    result->numerator = fraction.numerator + num * fraction.denominator;
    result->denominator = fraction.denominator;
    simplify(result);
    return *result;
}

Fraction multiFraction(Fraction a, Fraction b, Fraction *result)
{
    result->numerator = a.numerator * b.numerator;
    result->denominator = a.denominator * b.denominator;
    simplify(result);
    return *result;
}

Fraction multiNum(Fraction fraction, int num, Fraction *result)
{
    result->numerator = fraction.numerator * num;
    result->denominator = fraction.denominator;
    simplify(result);
    return *result;
}


Fraction inputFraction(Fraction *pFraction)
{
    int numerator;
    scanf("%d", &numerator);
    // 解析输入的字符串
    int temp;
    while ((temp = getchar()) != '\n' && temp == ' ')
        continue;
    if (temp == '\n')
    {
        initFraction(numerator, 1, pFraction);
        return *pFraction;
    }
    else if (temp == '/')
    {
        int denominator;
        scanf("%d", &denominator);
        while ((temp = getchar()) != '\n' && temp != ' ')
            continue;
        if (temp == '\n')
        {
            initFraction(numerator, denominator, pFraction);
            return *pFraction;
        } else
        {
            printf("Fraction输入错误!\n");
            exit(-1);
        }
    } else
    {
        printf("Fraction输入错误!\n");
        exit(-1);
    }
}

// 获取相反数
Fraction getOpposite(Fraction fraction, Fraction *result)
{
    result->numerator = -fraction.numerator;
    result->denominator = fraction.denominator;
    return *result;
}

// 获取分数的倒数
Fraction getCountdown(Fraction fraction, Fraction *result)
{
    if (fraction.numerator == 0)
    {
        printf("0没有倒数!\n");
        exit(-1);
    }
    result->denominator = fraction.numerator;
    result->numerator = fraction.denominator;
    if (result->denominator < 0)         // 不让分母带负号
    {
        result->numerator = - result->numerator;
        result->denominator = - result->denominator;
    }
    return *result;
}

// 判断分数是否为负
bool isNegative(Fraction fraction)
{
    if (fraction.numerator < 0)
        return true;
    return false;
}

