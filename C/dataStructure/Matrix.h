//
// Created by Anvei on 2022/10/9.
//
// 提供矩阵的基本实现

#ifndef ALGORITHM_MATRIX_H
#define ALGORITHM_MATRIX_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "Fraction.h"

typedef struct {
    Fraction *data;
    int row;
    int col;
} Matrix;

bool matrix_init(Matrix *pmatrix, int row, int col);

void matrix_destory(Matrix matrix);

Fraction matrix_get(Matrix matrix, int row_index, int col_index);

void matrix_set(Matrix matrix, int row_index, int col_index, Fraction frac);

Matrix matrix_multiply(Matrix a, Matrix b);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_MATRIX_H
