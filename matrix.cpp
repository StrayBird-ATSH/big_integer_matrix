//
// Created by zhang on 5/31/2019.
//

#include <cstring>
#include "matrix.h"
#include <algorithm>

matrix::matrix(std::string matrix[]) {
    for (int j = 0; j < 3; ++j) {
        int length = matrix[j].length();
        int separator1 = matrix[j].find_first_of(' ');
        int separator2 = matrix[j].substr(separator1 + 1, length - separator1).find(' ') + 1 + separator1;

        matrixContent[j][0] = big_integer(matrix[j].substr(0, separator1));
        matrixContent[j][1] = big_integer(matrix[j].substr(separator1 + 1, separator2 - separator1 - 1));
        matrixContent[j][2] = big_integer(matrix[j].substr(separator2 + 1, length - separator2 - 2));
    }
}
