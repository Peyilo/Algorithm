/**
 * @author Anvei
 * @date 2022/10/1
 */

#include <iostream>
#include "LinearAlgebra.h"
#include "util/Matrix.h"

int main(int argc, char *argv[])
{
    //system("chcp 65001");           // 执行DOS窗口命令，将窗口设置为UTF-8编码，防止中文出现乱码

    if (argc == 1)
        help();          // 打印提示信息

    /* 输入矩阵的行数列数 */
    int row = 0, col = 0;
    input_row_and_col(row, col);

    /* 输入矩阵元素 */
    Matrix matrix(row, col);
    matrix.input();
    std::cout << matrix << std::endl;

    /* 初等行变换 */
    matrix.transform(true);

    std::cout << "Press 'Enter' key to end the program . . .";
    std::cin.get();
    return 0;
}
