//
// Created by Anvei on 2022/9/24.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include "util/Fraction.h"
#include <stdbool.h>

typedef struct {
    Fraction * pFraction;    // 表示矩阵首元素
    int row;
    int col;
} Matrix;

Matrix * initMatrix(int row, int col);

void destroyMatrix(Matrix *pmatrix);

void inputMatrix(Matrix *pMatrix);

Fraction *getFraction(Matrix matrix, int rowIndex, int colIndex);

void setFraction(Matrix *pMatrix, int rowIndex, int colIndex, Fraction fraction);

void printMatrix(Matrix matrix);

Matrix *multiMatrix(Matrix a, Matrix b);

Matrix transformation(Matrix *pMatrix, int colIndex, bool flag);

int calcTransResult(Matrix *pMatrix, bool flag);

Matrix simplifyRow(Matrix *pMatrix, int rowIndex);

int getRank_A(Matrix matrix);

int getRank_B(Matrix matrix);

void swapRow(Matrix *pMatrix, int rowIndex1, int rowIndex2);

Matrix * getRowVector(Matrix matrix, int rowIndex);

void multiNumToRow(Matrix *pMatrix, int rowIndex, int k);

void multiFractionToRow(Matrix *pMatrix, int rowIndex, Fraction fraction);

void addVectorTorRow(Matrix *pMatrix, int rowIndex, Fraction fraction, Matrix *vector);

void addRowToRow(Matrix *pMatrix, int rowIndex1, Fraction fraction, int rowIndex2);

#endif //MATRIX_MATRIX_H
