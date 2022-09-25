#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void)
{
    system("chcp 65001");           // 执行DOS窗口命令，将窗口设置为UTF-8编码，防止中文出现乱码
//  ==============main函数主体计算部分===============
    int row = 0, col = 0;
    printf("Please enter the number of rows and columns of the matrix (example: 3*4):  ");
    scanf("%d*%d", &row, &col);

    Matrix *pMatrix = initMatrix(row, col);
    inputMatrix(pMatrix);           // 处理输入
    printMatrix(*pMatrix);

    calcTransResult(pMatrix, true);     // 进行初等行变换

    destroyMatrix(pMatrix);             // 释放内存
    printf("Press 'Enter' key to end the program . . .");
    getchar();
    return 0;
}
