//
// Created by Anvei on 2022/10/9.
//

#include "Matrix.h"
#include <stdlib.h>

/**
 * 矩阵的初始化
 * @param pmatrix
 * @param row
 * @param col
 * @return
 */
bool matrix_init(Matrix *pmatrix, int row, int col)
{
    Fraction *temp = malloc(sizeof(Fraction) * row * col);
    if (!temp) return false;
    pmatrix->data = temp;
    pmatrix->row = row;
    pmatrix->col = col;
    return true;
}

/**
 * 释放矩阵的内存
 * @param pmatrix
 */
void matrix_destory(Matrix matrix)
{
    free(matrix.data);
}

/**
 * 获取矩阵指定下标的Fraction地址
 * @param matrix
 * @param row_index
 * @param col_index
 * @return
 */
Fraction matrix_get(Matrix matrix, int row_index, int col_index)
{
    return *(matrix.data + (row_index - 1) * matrix.col + col_index - 1);
}

/**
 * 为矩阵指定下标的Fraction赋值
 * @param matrix
 * @param row_index
 * @param col_index
 * @param frac
 */
void matrix_set(Matrix matrix, int row_index, int col_index, Fraction frac)
{
    *(matrix.data + (row_index - 1) * matrix.col + col_index - 1) = frac;
}

/**
 * 计算矩阵与矩阵相乘的结果，返回的矩阵指针记得需要释放以防指针泄露
 * 矩阵a的列数必须和矩阵b的行数相等
 * @param a
 * @param b
 * @return
 */
Matrix matrix_multiply(Matrix a, Matrix b)
{
    Matrix res;
    matrix_init(&res, a.row, b.col);
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < b.col; j++)
        {
            Fraction sum = {0, 1};
            for (int k = 0; k < a.col; k++)
            {
                Fraction temp = frac_multiply_frac(matrix_get(a, i + 1, k + 1),
                                   matrix_get(b, j + 1, k + 1));
                sum = frac_add_frac(sum, temp);
            }
            matrix_set(res, i + 1, j + 1, sum);
        }
    }
    return res;
}
