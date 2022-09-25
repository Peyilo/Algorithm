//
// Created by Anvei on 2022/9/24.
//

#ifndef MATRIX_FRACTION_H
#define MATRIX_FRACTION_H
#include <stdbool.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction initFraction(int numerator, int denominator, Fraction *pFraction);

void simplify(Fraction *pFraction);

Fraction addFraction(Fraction a, Fraction b, Fraction *result);

Fraction addNum(Fraction fraction, int num, Fraction *result);

Fraction multiFraction(Fraction a, Fraction b, Fraction *result);

Fraction multiNum(Fraction fraction, int num, Fraction *result);

Fraction inputFraction(Fraction *pFraction);

Fraction getCountdown(Fraction fraction, Fraction *result);

bool isNegative(Fraction fraction);

Fraction getOpposite(Fraction fraction, Fraction *result);

#endif //MATRIX_FRACTION_H
