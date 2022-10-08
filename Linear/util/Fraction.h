//
// Created by Anvei on 2022/10/1.
//

#ifndef LINEARALGEBRA_FRACTION_H
#define LINEARALGEBRA_FRACTION_H
#include <iostream>

/* 定义了分数的通用操作 */
class Fraction {
private:
    int mNumerator;
    int mDenominator;
    void simplify();
public:
    Fraction() : Fraction(0, 1) {};
    explicit Fraction(int interge) : Fraction(interge, 1) {};
    Fraction(int numer, int denomin);
    Fraction(const Fraction &fraction);

    int get_numerator() const;
    int get_denominator() const;
    void set_numerator(int numer);
    void set_denominator(int denomin);
    void set_fraction(const Fraction &fraction);
    void set_fraction(int numer, int denomin);

    bool isNegative() const;
    Fraction opposite() const;
    Fraction countdown() const;

    Fraction operator+(const Fraction &fraction) const;
    Fraction operator-(const Fraction &fraction) const;
    Fraction operator*(const Fraction &fraction) const;
    Fraction operator/(const Fraction &fraction) const;
    bool operator==(const Fraction &fraction) const;
    bool operator!=(const Fraction &fraction) const;
    Fraction operator+(int num) const;
    Fraction operator-(int num) const;
    Fraction operator*(int num) const;
    Fraction operator/(int num) const;
    bool operator==(int num) const;
    bool operator!=(int num) const;
    friend Fraction operator+(int num, const Fraction& fraction);
    friend Fraction operator-(int num, const Fraction& fraction);
    friend Fraction operator*(int num, const Fraction& fraction);
    friend Fraction operator/(int num, const Fraction& fraction);
    friend bool operator==(int num, const Fraction &fraction);
    friend bool operator!=(int num, const Fraction &fraction);

    explicit operator int() const;
    explicit operator double() const;

    friend std::ostream &operator<<(std::ostream &os, const Fraction &fraction);
    friend std::istream &operator>>(std::istream &is, Fraction &fraction);
};


#endif //LINEARALGEBRA_FRACTION_H
