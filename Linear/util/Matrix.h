//
// Created by Anvei on 2022/10/1.
//

#ifndef LINEARALGEBRA_MATRIX_H
#define LINEARALGEBRA_MATRIX_H
#include <vector>
#include <iostream>
#include "Fraction.h"

class Matrix {
    /* 数据成员 */
private:
    int row;
    int col;
    std::vector<Fraction> vec;
    /* 内部私有函数 */
private:
    int select(int col_index, bool flag);
    int rank() const;
    /* 构造函数成员 */
public:
    Matrix() : Matrix(0 ,0) {};
    Matrix(int row, int col);
    Matrix(Matrix const &matrix);       // 拷贝构造函数
    void set(int row_index, int col_index, const Fraction &fraction);
    void set(int row_index, int col_index, int val);
    int get_row() const;
    int get_col() const;
    void input();
    Matrix get_row_matrix(int row_index) const;
    void set_row_matrix(int row_index, const Matrix &row_matrix);
    void multi_row(int row_index, int k);
    void multi_row(int row_index, const Fraction &k);
    void add_row(int row_index, const Matrix &row_matrix);
    void swap_row(int row1, int row2);
    /* 对矩阵进行简化处理 */
    void simplify();
    void simplify(bool flag);
    void simplify(int row_index);
    void simplify(int row_index, bool flag);
    /* 求矩阵的秩 */
    int rank_A() const;
    int rank_B() const;
    /* 初等行变换 */
    void transform(int col_index);
    void transform(int col_index, bool flag);
    void transform();
    void transform(bool flag);
    /* 操作符重载 */
    Matrix operator*(const Matrix &matrix) const;
    Fraction operator() (int row_index, int col_index) const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

};


#endif //LINEARALGEBRA_MATRIX_H
