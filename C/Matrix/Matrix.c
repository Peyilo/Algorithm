//
// Created by Anvei on 2022/9/24.
//

#include "Matrix.h"
#include "util/util.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化矩阵
Matrix * initMatrix(int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("矩阵初始化错误!矩阵的行数列数必须大于0!\n");
        exit(-1);
    }
    Matrix *pMatrix = malloc(sizeof(Matrix));
    pMatrix->row = row;
    pMatrix->col = col;
    pMatrix->pFraction = malloc(sizeof(Fraction) * row * col);
    return pMatrix;
}

// 释放矩阵的内存
void destroyMatrix(Matrix *pmatrix)
{
    free(pmatrix->pFraction);
    free(pmatrix);
}

// 处理矩阵的输入
void inputMatrix(Matrix *pMatrix)
{
    int row = pMatrix->row, col = pMatrix->col;
    puts("Input the matrix......");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("Matrix row %d, column %d:  ", i + 1, j + 1);
            inputFraction(getFraction(*pMatrix, i + 1, j + 1));
        }
    }
}

// 获取矩阵指定下标的Fraction地址
Fraction *getFraction(Matrix matrix, int rowIndex, int colIndex)
{
    return matrix.pFraction + (rowIndex - 1) * matrix.col + colIndex - 1;
}

// 为矩阵指定下标的Fraction赋值
void setFraction(Matrix *pMatrix, int rowIndex, int colIndex, Fraction fraction)
{
    Fraction *pFraction = getFraction(*pMatrix, rowIndex, colIndex);
    pFraction->numerator = fraction.numerator;
    pFraction->denominator = fraction.denominator;
}

// 打印矩阵
void printMatrix(Matrix matrix)
{
    printf("Matrix%d*%d:\n", matrix.row, matrix.col);
    for (int i = 0; i < matrix.row; i++)
    {
        putchar('\t');
        for (int j = 0; j < matrix.col; j++)
        {
            Fraction *pFraction = getFraction(matrix, i + 1, j + 1);
            if (pFraction->denominator == 1)
                printf("%5d  ", pFraction->numerator);
            else
                printf("%2d/%-2d  ", pFraction->numerator, pFraction->denominator);
        }
        putchar('\n');
    }
}

// 计算矩阵与矩阵相乘的结果
Matrix *multiMatrix(Matrix a, Matrix b)
{
    if (a.col != b.row) {
        printf("矩阵的维数有误!\n");
        exit(-1);
    }
    Matrix *pMatrix = initMatrix(a.row, b.col);
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < b.col; j++)
        {
            Fraction sum = {
                    .numerator = 0,
                    .denominator = 1
            };
            for (int k = 0; k < a.col; k++)
            {
                Fraction temp;
                multiFraction(*getFraction(a, i + 1, k + 1),
                              *getFraction(b, j + 1, k + 1), &temp);
                addFraction(sum, temp, &sum);
            }
            setFraction(pMatrix, i + 1, j + 1, sum);
        }
    }
    return pMatrix;
}

// 获取行向量，记得释放该指针
Matrix * getRowVector(Matrix matrix, int rowIndex)
{
    Matrix *vector = initMatrix(1, matrix.col);
    for (int i = 0; i < matrix.col; i++)
    {
        Fraction *pFraction = getFraction(matrix, rowIndex, i+1);
        setFraction(vector, 1, i + 1, *pFraction);
    }
    return vector;
}

// 对矩阵某行乘上一个非0常数k
void multiNumToRow(Matrix *pMatrix, int rowIndex, int k)
{
    if (k == 0)             // 处理k=0的情形
    {
        printf("time:%s, file:%s, line；%d, ERROR: k不能为0!", __TIME__, __FILE__, __LINE__);
        exit(-1);
    }
    for (int i = 0; i < pMatrix->col; i++)
    {
        Fraction *pFraction = getFraction(*pMatrix, rowIndex, i + 1);
        multiNum(*pFraction, k, pFraction);
    }
}

// 对矩阵某行乘上一个非0分数
void multiFractionToRow(Matrix *pMatrix, int rowIndex, Fraction fraction)
{
    if (fraction.numerator == 0)             // 处理k=0的情形
    {
        printf("time:%s, file:%s, line；%d, ERROR...", __TIME__, __FILE__, __LINE__);
        exit(-1);
    }
    for (int i = 0; i < pMatrix->col; i++)
    {
        Fraction *pFraction = getFraction(*pMatrix, rowIndex, i + 1);
        multiFraction(*pFraction, fraction, pFraction);
    }
}

// 对矩阵的rowIndex行加上一个kri
void addVectorTorRow(Matrix *pMatrix, int rowIndex, Fraction fraction, Matrix *vector)
{
    if (pMatrix->col != vector->col)
    {
        printf("矩阵相加错误!\n");
        exit(-1);
    }
    if (vector->row != 1)
    {
        printf("请输入一个行向量!\n");
        exit(-1);
    }
    multiFractionToRow(vector, 1, fraction);
    for (int i = 0; i < pMatrix->col; i++)
    {
        Fraction *pFraction = getFraction(*vector, 1, i + 1);
        Fraction calcRes;
        addFraction(*pFraction, *getFraction(*pMatrix, rowIndex, i + 1), &calcRes);
        setFraction(pMatrix, rowIndex, i + 1, calcRes);
    }
}

void addRowToRow(Matrix *pMatrix, int rowIndex1, Fraction fraction, int rowIndex2)
{
    Matrix *vector = getRowVector(*pMatrix, rowIndex2);
    addVectorTorRow(pMatrix, rowIndex1, fraction, vector);
    destroyMatrix(vector);
}

// 将矩阵某行化为最简形式
Matrix simplifyRow(Matrix *pMatrix, int rowIndex)
{
    int col = pMatrix->col, count = 0;      // count对非0项计数
    for (int i = 0; i < col; i++)
        if (getFraction(*pMatrix, rowIndex, i + 1)->numerator != 0)
            count++;
    if (count == 0)                         // 表示所有项全为0
        return *pMatrix;
    int list[count];
    count = 0;
    for (int i = 0; i < col; i++)           // 将所有非零项添加进数组list中
    {
        Fraction *pFraction = getFraction(*pMatrix, rowIndex, i + 1);
        if (pFraction->numerator != 0)
            list[count++] = pFraction->denominator;
    }
    int lcmNum = lcm_n(count, list);        // 求出最小公倍数lcmNum以后，将其与矩阵相应的行相乘
    multiNumToRow(pMatrix, rowIndex, lcmNum);   // 使该行所有fraction的分母为1
    count = 0;
    for (int i = 0; i < col; i++)           // 求出最大公约数，对该行所有项进行约分
    {
        Fraction *pFraction = getFraction(*pMatrix, rowIndex, i + 1);
        if (pFraction->numerator != 0)
            list[count++] = pFraction->numerator;
    }
    int gcdNum = gcd_n(count, list);
    if (gcdNum != 1)
    {
        Fraction temp;
        initFraction(1, gcdNum, &temp);
        multiFractionToRow(pMatrix, rowIndex, temp);
    }

    // 使该行首个非零项为1
    for (int i = 0; i < pMatrix->col; i++)
    {
        Fraction *temp = getFraction(*pMatrix, rowIndex, i + 1);
        if (temp->numerator != 0)
        {
            Fraction temp0;
            initFraction(temp->denominator, temp->numerator, &temp0);
            multiFractionToRow(pMatrix, rowIndex, temp0);
            break;
        }
    }
    return *pMatrix;
}

// 交换矩阵的指定两行
void swapRow(Matrix *pMatrix, int rowIndex1, int rowIndex2)
{
    Matrix *temp = getRowVector(*pMatrix, rowIndex1);
    for (int i = 0; i < pMatrix->col; i++)
    {
        *getFraction(*pMatrix, rowIndex1, i + 1) = *getFraction(*pMatrix, rowIndex2, i + 1);
        *getFraction(*pMatrix, rowIndex2, i + 1) = *getFraction(*temp, 1, i + 1);
    }
    destroyMatrix(temp);
}

// 计算矩阵的秩，输入的矩阵必须是阶梯矩阵形式
int getRank_B(Matrix matrix)
{
    int rank = 0;
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            if (getFraction(matrix, i + 1, j + 1)->numerator != 0)
            {
                rank++;
                break;
            }
        }
    }
    return rank;
}

// 用来计算matrix除去最后一列的秩，主要用来处理系数矩阵的秩的计算
int getRank_A(Matrix matrix)
{
    int rank = 0;
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col - 1; j++)
        {
            if (getFraction(matrix, i + 1, j + 1)->numerator != 0)
            {
                rank++;
                break;
            }
        }
    }
    return rank;
}

// 根据情况选择哪一行作为基础行，供内部函数调用
static int selectRow(Matrix matrix, int colIndex, bool flag)
{
    int res = -1, tempIndex = -1;
    for (int i = 0; i < matrix.row; i++)
    {
        Fraction *temp = getFraction(matrix, i + 1, colIndex);
        if (temp->numerator != 0)
        {
            bool flag0 = true;
            Fraction *temp0;
            for (int j = 1; j < colIndex; j++)
            {
                temp0 = getFraction(matrix, i + 1, j);
                if (temp0->numerator != 0)
                {
                    flag0 = false;
                    break;
                }
            }
            if (flag0)              // colIndex列之前的列全部为0就执行以下语句
            {
                if (tempIndex == -1)
                    tempIndex = i + 1;
                if (temp->numerator == temp->denominator)
                {
                    res = i + 1;
                    break;
                }
                if (res == -1)
                    res = i + 1;
            }
        }
    }
    if (res != -1 && res != tempIndex)
    {
        swapRow(&matrix, res, tempIndex);
        if (flag)
        {
            printf("#Swap Row%d <-> Row%d:\n", tempIndex, res);
            printMatrix(matrix);
        }
    }
    return tempIndex;
}

// 进行一轮初等行变换
Matrix transformation(Matrix *pMatrix, int colIndex, bool flag)
{
    int row = pMatrix->row, col = pMatrix->col;
    int basicIndex = selectRow(*pMatrix, colIndex, flag);
    if (basicIndex == -1)
        return *pMatrix;
    for (int i = basicIndex; i < pMatrix->row; i++)
    {
        Fraction multiplier;
        Fraction *temp1 = getFraction(*pMatrix, basicIndex, colIndex);
        Fraction *temp2 = getFraction(*pMatrix, i + 1, colIndex);
        if (temp2->numerator == 0)
            continue;
        getCountdown(*temp1, &multiplier);
        multiFraction(multiplier, *temp2, &multiplier);
        multiplier.numerator = -multiplier.numerator;
        addRowToRow(pMatrix, i + 1, multiplier, basicIndex);
        if (flag)       // 打印运算信息
        {
            if (multiplier.denominator == 1)
            {
                if (multiplier.numerator > 0)
                    printf("#Calc Row%d + %d * Row%d:\n", i + 1, multiplier.numerator, basicIndex);
                else
                    printf("#Calc Row%d - %d * Row%d:\n", i + 1, -multiplier.numerator, basicIndex);
            }
            else
            {
                if (multiplier.numerator > 0)
                    printf("#Calc Row%d + %d/%d * Row%d:\n", i + 1, multiplier.numerator,
                           multiplier.denominator, basicIndex);
                else
                    printf("#Calc Row%d - %d/%d * Row%d:\n", i + 1, -multiplier.numerator,
                           multiplier.denominator, basicIndex);
            }
            printMatrix(*pMatrix);
        }
    }
    return *pMatrix;
}

// 计算初等行变换最终结果，返回矩阵的秩
int calcTransResult(Matrix *pMatrix, bool flag)
{
    for (int i = 0; i < pMatrix->col; i++)
        transformation(pMatrix, i + 1, flag);
    for (int i = 0; i < pMatrix->row; i++)
        simplifyRow(pMatrix, i + 1);
    int rank = getRank_B(*pMatrix);
    printf("#Result Rank = %d:\n", rank);
    printMatrix(*pMatrix);
    return rank;
}
