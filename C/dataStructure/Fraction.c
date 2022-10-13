//
// Created by Anvei on 2022/10/9.
//

#include "Fraction.h"
#include "../number/digitalutils.h"

/**
 * 对分数进行约分、保证分母必为正数、保证分数值为0时，分母被设为1，
 * @param pfrac
 */
void frac_simplify(Fraction *pfrac)
{
    if (!pfrac->denominator) return;        // 如果分母为0不做处理，等待后续操作自行出错
    if (!pfrac->numerator)
    {
        pfrac->denominator = 1;
        return;
    }
    int gcd_val = gcd(pfrac->numerator, pfrac->denominator);    // 约分
    pfrac->denominator /= gcd_val;
    pfrac->numerator /= gcd_val;
    if (pfrac->denominator < 0)                 // 保证分母为正
    {
        pfrac->denominator = -pfrac->denominator;
        pfrac->numerator = -pfrac->numerator;
    }
}

/**
 * 分数和int值的相加
 * @param frac
 * @param num
 * @return
 */
Fraction frac_add_num(Fraction frac, int num)
{
    frac.numerator += frac.denominator * num;
    frac_simplify(&frac);
    return frac;
}

/**
 * 分数与分数之间的相加
 * @param a
 * @param b
 * @return
 */
Fraction frac_add_frac(Fraction a, Fraction b)
{
    a.numerator = a.denominator * b.numerator + a.numerator * b.denominator;
    a.denominator = a.denominator * b.denominator;
    frac_simplify(&a);
    return a;
}

/**
 * 分数与int值的相乘
 * @param frac
 * @param num
 * @return
 */
Fraction frac_multiply_num(Fraction frac, int num)
{
    frac.numerator *= num;
    frac_simplify(&frac);
    return frac;
}

/**
 * 分数之间的相乘
 * @param a
 * @param b
 * @return
 */
Fraction frac_multiply_frac(Fraction a, Fraction b)
{
    a.denominator *= b.denominator;
    a.numerator *= b.numerator;
    frac_simplify(&a);
    return a;
}

/**
 * 返回分数对应的整数值，可能会有精度损失
 * @param frac
 * @return
 */
int frac_int(Fraction frac)
{
    return frac.numerator / frac.denominator;
}

/**
 * 返回分数对应的双精度浮点数值
 * @param frac
 * @return
 */
double frac_double(Fraction frac)
{
    return (double) frac.numerator / frac.denominator;
}

/**
 * 将一个整数转换为分数
 * @param integer
 * @return
 */
Fraction frac_trans_int(int integer)
{
    Fraction res = {integer, 1};
    return res;
}

/**
 * 将一个双精度浮点数转换为分数
 * @param decimal
 * @param precision
 * @return
 */
Fraction frac_trans_double(double decimal, int precision)
{
    Fraction res;
    return res;
}

/**
 * 获取分数的相反数
 * @param frac
 * @return
 */
Fraction frac_opposite(Fraction frac)
{
    frac.numerator = -frac.numerator;
    frac_simplify(&frac);
    return frac;
}

/**
 * 获取分数的倒数
 * @param frac
 * @return
 */
Fraction frac_countdown(Fraction frac)
{
    int temp = frac.numerator;
    frac.numerator = frac.denominator;
    frac.denominator = temp;
    frac_simplify(&frac);
    return frac;
}

