//
// Created by Anvei on 2022/10/2.
//

#include "../util/Matrix.h"
#include <iostream>

using namespace std;
int main()
{
    Matrix matrix(2, 4);
    for (int i = 0; i < matrix.get_row(); i++) {
        for (int j = 0; j < matrix.get_col(); j++) {
            cout << matrix(i + 1, j + 1);
        }
    }
    return 0;
}