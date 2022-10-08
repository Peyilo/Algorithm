//
// Created by Anvei on 2022/10/1.
//

#include "Matrix.h"
#include <iomanip>

Matrix::Matrix(int row, int col) {
    this->row = row;
    this->col = col;
    vec = std::vector<Fraction>(row * col);
}

Matrix::Matrix(const Matrix &matrix) {
    row = matrix.row;
    col = matrix.col;
    for (int i = 0; i < row * col; i++)
        vec[i] = matrix.vec[i];
}

/**
 * 获取矩阵指定行标列标元素
 * @param row_index
 * @param col_index
 * @return
 */
Fraction Matrix::operator()(int row_index, int col_index) const {
    return vec[(row_index - 1) * col + col_index - 1];
}

/**
 * 为矩阵指定行标列标元素设置值
 * @param row_index
 * @param col_index
 * @param fraction
 */
void Matrix::set(int row_index, int col_index, const Fraction &fraction) {
    vec[(row_index - 1) * col + col_index - 1] = fraction;
}

void Matrix::set(int row_index, int col_index, int val) {
    set(row_index, col_index, Fraction(val));
}
/**
 * 获取矩阵的行数
 * @return
 */
int Matrix::get_row() const {
    return row;
}

/**
 * 获取矩阵的列数
 * @return
 */
int Matrix::get_col() const {
    return col;
}
/**
 * 从键盘获取输入
 */
void Matrix::input() {
    std::cout << "Input the matrix:" << std::endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << "#Input [" << i + 1 << ", " << j + 1 << "]: ";
            std::cin >> vec[i * col + j];
        }
    }
}

/**
 * 操作符<<重载，支持使用<<直接向屏幕输出矩阵
 * @param os
 * @param matrix
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    os << "Matrix" << matrix.row << "*" << matrix.col << ":\n";
    for (int i = 0; i < matrix.row; i++)
    {
        os << "  ";
        for (int j = 0; j < matrix.col; j++) {
            os << std::setw(5) << matrix(i + 1, j + 1) << " ";
        }
        os << std::endl;
    }
    return os;
}

/**
 * 操作符*重载，支持矩阵之间的相乘
 * @param matrix
 * @return
 */
Matrix Matrix::operator*(const Matrix &matrix) const {
    if (col != matrix.row) {
        std::cout << "矩阵的维数有误!" << std::endl;
        exit(-1);
    }
    Matrix res(row, matrix.col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            Fraction sum(0);        // 初始化为0
            for (int k = 0; k < col; k++)
                sum = sum + (*this)(i + 1, k + 1) * matrix(j + 1, k + 1);
            res.set(i + 1, j + 1, sum);
        }
    }
    return res;
}

/**
 * 获取指定行标的单行矩阵
 * @param row_index
 * @return
 */
Matrix Matrix::get_row_matrix(int row_index) const {
    Matrix res(1, col);
    for (int i = 0; i < col; i++)
        res.set(1, i + 1, (*this)(row_index, i + 1));
    return res;
}

/**
 * 使用单行矩阵为矩阵指定的行标赋值
 * @param row_index
 * @param row_matrix
 */
void Matrix::set_row_matrix(int row_index, const Matrix &row_matrix) {
    if (row_matrix.row != 1) {
        std::cout << "只能使用单行矩阵设置!" << std::endl;
        exit(-1);
    }
    if (row_matrix.col != col) {
        std::cout << "该单行矩阵变量的列数必须与本矩阵行数相等!" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < col; i++)
        set(row_index, i + 1, row_matrix(1, i + 1));
}

/**
 * 对矩阵指定行乘上一个int值
 * @param row_index
 * @param k
 */
void Matrix::multi_row(int row_index, int k) {
    multi_row(row_index, Fraction(k));
}

/**
 * 对矩阵指定行乘上一个Fraction值
 * @param row_index
 * @param k
 */
void Matrix::multi_row(int row_index, const Fraction &k) {
    for (int i = 0; i < col; i++)
        set(row_index, i + 1, (*this)(row_index, i + 1) * k);
}

/**
 * 对矩阵指定行加上一个单行矩阵
 * @param row_index
 * @param row_matrix
 */
void Matrix::add_row(int row_index, const Matrix &row_matrix) {
    if (row_matrix.row != 1) {
        std::cout << "只能使用单行矩阵相加!" << std::endl;
        exit(-1);
    }
    if (row_matrix.col != col) {
        std::cout << "该单行矩阵变量的列数必须与本矩阵行数相等!" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < col; i++)
        set(row_index, i + 1,
            (*this)(row_index, i + 1) + row_matrix(1, i + 1));
}

/**
 * 交换矩阵的指定两行
 * @param row1
 * @param row2
 */
void Matrix::swap_row(int row1, int row2) {
    Matrix temp = get_row_matrix(row1);
    set_row_matrix(row1, get_row_matrix(row2));
    set_row_matrix(row2, temp);
}

void Matrix::simplify() {
    simplify(false);
}

void Matrix::simplify(bool flag) {
    for (int i = 0; i < row; i++)
        simplify(i + 1, flag);
}

void Matrix::simplify(int row_index) {
    simplify(row_index, false);
}

/**
 * 对矩阵指定行进行简化
 * @param row_index
 * @param flag true表示打印具体处理信息，false不打印
 */
void Matrix::simplify(int row_index, bool flag) {
    for (int i = 0; i < col; i++)
    {
        Fraction temp = (*this)(row_index, i + 1);
        if (temp == 1)
            break;
        if (temp != 0)
        {
            multi_row(row_index, temp.countdown());
            if (flag)
            {
                std::cout << "#Calc: " << temp.countdown() << " * r" << row_index << std::endl;
                std::cout << *this;
            }
            break;
        }
    }
}

/**
 * 只能由行阶梯矩阵调用才会得到正确的值
 * @return
 */
int Matrix::rank() const {
    int R = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((*this)(i + 1, j + 1) != 0)
            {
                R++;
                break;
            }
        }
    }
    return R;
}

/**
 * 获取矩阵除去最后一列的秩
 * @return
 */
int Matrix::rank_A() const {
    Matrix temp(*this);
    temp.transform();
    int R = 0;
    for (int i = 0; i < temp.row; i++)
    {
        for (int j = 0; j < temp.col - 1; j++)
        {
            if (temp(i + 1, j + 1) != 0)
            {
                R++;
                break;
            }
        }
    }
    return R;
}

/**
 * 获取矩阵的秩
 * @return
 */
int Matrix::rank_B() const {
    Matrix temp(*this);
    temp.transform();
    return temp.rank();
}

void Matrix::transform(int col_index) {
    transform(col_index, false);
}

/**
 * 对矩阵指定列进行一轮初等行变换
 * @param col_index
 * @param flag  控制是否打印矩阵处理信息
 */
void Matrix::transform(int col_index, bool flag) {
    int index = select(col_index, flag);
    if (index == -1)
        return ;
    for (int i = index; i < row; i++)
    {
        if ((*this)(i + 1, col_index) == 0)
            continue;
        Fraction multiplier = ((*this)(index, col_index).countdown() *
                               (*this)(i + 1, col_index)).opposite();
        Matrix single_row = get_row_matrix(index);
        single_row.multi_row(1, multiplier);
        add_row(i + 1, single_row);
        if (flag)       // 打印运算信息
        {
            if (multiplier.isNegative())
                std::cout << "#Calc r" << i + 1 << " - " << multiplier.opposite() <<
                            " * r" << index << ":" << std::endl;
            else
                std::cout << "#Calc r" << i + 1 << " + " << multiplier <<
                          " * r" << index << ":" << std::endl;
            std::cout << *this << std::endl;
        }
    }
}

void Matrix::transform() {
    transform(false);
}

void Matrix::transform(bool flag) {
    for (int i = 0; i < col; i++)
        transform(i + 1, flag);
    simplify(flag);
    if (flag)
    {
        int R = rank();
        std::cout << "#Result Rank = " << R << ":" << std::endl;
        std::cout << *this << std::endl;
    }
}

/**
 * 供类内部函数作初等行变换时调用，用于选定哪一行作为最佳基础行
 * @param col_index
 * @return
 */
int Matrix::select(int col_index, bool flag){
    int res = -1, first = -1;
    for (int i = 0; i < row; i++)
    {
        Fraction temp_val1 = (*this)(i + 1, col_index);
        if (temp_val1 != 0)
        {
            bool temp_flag = true;
            Fraction temp_val2;
            for (int j = 1; j < col_index; j++)
            {
                temp_val2 = (*this)(i + 1, j);
                if (temp_val2 != 0)
                {
                    temp_flag = false;
                    break;
                }
            }
            if (temp_flag)      // 如果在该行在col_index之前的元素全为0，就执行该条件语句
            {
                if (first == -1)
                    first = i + 1;     // 记录查询到第一个的符合条件的行标
                if (temp_val1 == 1 || temp_val1 == -1)
                {
                    res = i + 1;            // 试着查询最优行标（首个非零元素为1）
                    break;
                }
            }
        }
    }
    // res!=1表示查询到了一个首个非零元素为1的行
    if (res != -1 && res != first)
    {
        swap_row(res, first);
        if (flag)
        {
            std::cout << "#Swap r" << first << " <-> r" << res << ":" << std::endl;
            std::cout << *this;
        }
    }
    return first;
}

