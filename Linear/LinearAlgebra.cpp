//
// Created by Anvei on 2022/10/1.
//

#include "LinearAlgebra.h"
#include <iostream>

using std::cout;
using std::endl;

/* 打印提示信息 */
void help()
{

}

void input_row_and_col(int &row, int &col)
{
    std::cout << "Please enter the number of rows and columns of the matrix (example: 3*4):  ";
    int temp;
    std::cin >> row;
    while((temp = getchar()) != '\n' && temp == ' ')
        continue;
    if (temp != '*')
    {
        std::cout << "Input error!" << std::endl;
        exit(-1);
    }
    else
        std::cin >> col;
}