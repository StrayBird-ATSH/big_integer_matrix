//
// Created by zhang on 5/31/2019.
//

#include <cstring>
#include "matrix.h"
#include <algorithm>

matrix::matrix(std::string matrix[]) {
    for (int j = 0; j < 3; ++j) {
        int separator_1 = matrix[j].find_first_of(' ');
        int separator_2 = matrix[j].find_last_of(' ');
        int length = matrix[j].length();

        matrix_content[j][0] = big_integer(matrix[j].substr(0, separator_1));
        matrix_content[j][1] = big_integer(matrix[j].substr(separator_1, separator_2 - separator_1));
        matrix_content[j][2] = big_integer(matrix[j].substr(separator_2, length - separator_2));
    }
}
