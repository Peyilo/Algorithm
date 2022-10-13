//
// Created by Anvei on 2022/10/9.
//
// 提供分数的基本实现

#ifndef ALGORITHM_FRACTION_H
#define ALGORITHM_FRACTION_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct {
    int numerator;      // 分子
    int denominator;    // 分母
} Fraction;

void frac_simplify(Fraction *pfrac);

Fraction frac_add_num(Fraction frac, int num);

Fraction frac_add_frac(Fraction a, Fraction b);

Fraction frac_multiply_num(Fraction frac, int num);

Fraction frac_multiply_frac(Fraction a, Fraction b);

int frac_int(Fraction frac);

double frac_double(Fraction frac);

Fraction frac_trans_int(int integer);

Fraction frac_trans_double(double decimal, int precision);

Fraction frac_opposite(Fraction frac);

Fraction frac_countdown(Fraction frac);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_FRACTION_H
