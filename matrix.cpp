//
// Created by zhang on 5/31/2019.
//

#include <cstring>
#include "matrix.h"
#include <algorithm>

matrix::matrix(std::string matrix[]) {
    for (int j = 0; j < 9; ++j)
        matrixContent[j / 3][j % 3] = big_integer(matrix[j]);
}
