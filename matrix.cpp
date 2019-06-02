//
// Created by zhang on 5/31/2019.
//

#include <cstring>
#include "matrix.h"
#include <algorithm>

matrix::matrix(std::string matrix[]) {
    for (int j = 0; j < 3; ++j) {
        int separator1 = matrix[j].find_first_of(' ');
        int separator2 = matrix[j].find_last_of(' ');
        int length = matrix[j].length();

        matrixContent[j][0] = big_integer(matrix[j].substr(0, separator1));
        matrixContent[j][1] = big_integer(matrix[j].substr(separator1, separator2 - separator1));
        matrixContent[j][2] = big_integer(matrix[j].substr(separator2, length - separator2));
    }
}

matrix::matrix(matrix &originalMatrix) {
    for (int j = 0; j < 9; ++j)
        matrixContent[j / 3][j % 3] = big_integer(originalMatrix.matrixContent[j / 3][j % 3]);
}
