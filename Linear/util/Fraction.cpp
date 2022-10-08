//
// Created by Anvei on 2022/10/1.
//

#include "Fraction.h"
#include "num_process.h"
#include <iomanip>
Fraction::Fraction(int numer, int denomin) {
    if (denomin == 0) {
        std::cout << __FILE__ << ", "<< __LINE__ << " ERROR: 分子不能为0!" << std::endl;
        exit(-1);
    }
    mNumerator = numer;
    mDenominator = denomin;
    simplify();
}

Fraction::Fraction(const Fraction &fraction) {
    mNumerator = fraction.mNumerator;
    mDenominator = fraction.mDenominator;     // 通过fraction进行赋值时已经是最简形式
}

/**
 * 对分数进行约分、同时保证分数分母为正
 */
void Fraction::simplify() {
    if (mNumerator == 0) {
        mDenominator = 1;
        return;
    }
    if (mDenominator == 1)
        return;
    int gcd_num = gcd(mNumerator, mDenominator);
    if (gcd_num != 1) {
        mDenominator /= gcd_num;
        mNumerator /= gcd_num;
    }
    if (mDenominator < 0) {
        mDenominator = -mDenominator;
        mNumerator = -mNumerator;
    }
}

/**
 * 获取分数的分子
 * @return
 */
int Fraction::get_numerator() const {
    return mNumerator;
}

/**
 * 获取分数的分母
 * @return
 */
int Fraction::get_denominator() const {
    return mDenominator;
}

/**
 * 为分数的分母设置一个int值
 * @param denomin
 */
void Fraction::set_denominator(int denomin) {
    if (denomin == 0) {
        std::cout << __FILE__ << ", "<< __LINE__ << " ERROR: 分子不能为0!" << std::endl;
        exit(-1);
    }
    mDenominator = denomin;
    simplify();
}

void Fraction::set_numerator(int numer) {
    mNumerator = numer;
    simplify();
}

void Fraction::set_fraction(const Fraction &fraction) {
    mNumerator = fraction.mNumerator;
    mDenominator = fraction.mDenominator;     // 通过fraction进行赋值时已经是最简形式
}

void Fraction::set_fraction(int numer, int denomin) {
    if (denomin == 0) {
        std::cout << __FILE__ << ", "<< __LINE__ << " ERROR: 分子不能为0!" << std::endl;
        exit(-1);
    }
    mNumerator = numer;
    mDenominator = denomin;
    simplify();             // 简化
}

// 判断是否为负数
bool Fraction::isNegative() const {
    return mNumerator < 0;
}

// 获取相反数
Fraction Fraction::opposite() const {
    return {-mNumerator, mDenominator};
}

// 获取倒数
Fraction Fraction::countdown() const {
    if (mNumerator == 0) {
        std::cout << __FILE__ << ", "<< __LINE__ << " ERROR: 0没有倒数!" << std::endl;
        exit(-1);
    }
    return {mDenominator, mNumerator};
}


/* ===============运算符重载============== */

/*
 * 提供了对分数分数之间、分数与int类型之间的加减乘除运算符、等于不等于运算符、输入输出运算符的实现
 */

Fraction Fraction::operator+(const Fraction &fraction) const {
    int numer = mNumerator * fraction.mDenominator + mDenominator * fraction.mNumerator;
    int denomin = mDenominator * fraction.mDenominator;
    return {numer, denomin};
}

Fraction Fraction::operator-(const Fraction &fraction) const {
    int numer = mNumerator * fraction.mDenominator - mDenominator * fraction.mNumerator;
    int denomin = mDenominator * fraction.mDenominator;
    return {numer, denomin};
}

Fraction Fraction::operator*(const Fraction &fraction) const {
    int numer = mNumerator * fraction.mNumerator;
    int denomin = mDenominator * fraction.mDenominator;
    return {numer, denomin};
}

Fraction Fraction::operator/(const Fraction &fraction) const {
    if (fraction == 0) {
        std::cout << __FILE__ << ", "<< __LINE__ << " ERROR: 0不能做除数!" << std::endl;
        exit(-1);
    }
    int numer = mNumerator * fraction.mDenominator;
    int denomin = mDenominator * fraction.mNumerator;
    return {numer, denomin};
}

bool Fraction::operator==(const Fraction &fraction) const {
    if (mDenominator == fraction.mDenominator && mNumerator == fraction.mNumerator)
        return true;
    return false;
}

bool Fraction::operator!=(const Fraction &fraction) const {
    return !(*this == fraction);
}

Fraction Fraction::operator+(int num) const {
    Fraction temp(num, 1);
    return *this + temp;
}

Fraction Fraction::operator-(int num) const {
    Fraction temp(num, 1);
    return *this - temp;
}

Fraction Fraction::operator*(int num) const {
    Fraction temp(num, 1);
    return *this * temp;
}

Fraction Fraction::operator/(int num) const {
    Fraction temp(num, 1);
    return *this / temp;
}

bool Fraction::operator==(int num) const {
    if (mDenominator == 1 && mNumerator == num)
        return true;
    return false;
}

bool Fraction::operator!=(int num) const {
    return !(*this == num);
}

Fraction operator+(int num, const Fraction& fraction) {
    return fraction + num;
}

Fraction operator-(int num, const Fraction& fraction) {
    return fraction - num;
}

Fraction operator/(int num, const Fraction& fraction) {
    return fraction / num;
}

Fraction operator*(int num, const Fraction& fraction) {
    return fraction * num;
}

bool operator==(int num, const Fraction &fraction) {
    return fraction == num;
}

bool operator!=(int num, const Fraction &fraction) {
    return fraction != num;
}

std::ostream &operator<<(std::ostream &os, const Fraction &fraction) {
    if (fraction.mDenominator == 1)
        os << fraction.mNumerator;
    else
        os << fraction.mNumerator << "/" << std::left << fraction.mDenominator << std::right;
    return os;
}

std::istream &operator>>(std::istream &is, Fraction &fraction) {
    is >> fraction.mNumerator;
    // 解析输入的字符串
    int temp;
    while ((temp = getchar()) != '\n' && temp == ' ')
        continue;
    if (temp == '/')
    {
        is >> fraction.mDenominator;
        if (fraction.mDenominator == 0) {
            std::cout << __FILE__ << ", "<< __LINE__ << " ERROR: 分子不能为0!" << std::endl;
            exit(-1);
        }
        fraction.simplify();
        return is;
    } else
    {
        fraction.set_denominator(1);
        return is;
    }
}

Fraction::operator int() const {
    return mNumerator / mDenominator;
}

Fraction::operator double() const {
    return (double )mNumerator / mDenominator;
}

