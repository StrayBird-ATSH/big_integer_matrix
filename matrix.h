//
// Created by zhang on 5/31/2019.
//

#ifndef BIGNUMMATRIX_MATRIX_H
#define BIGNUMMATRIX_MATRIX_H

#include "big_integer.h"
#include <string>

class matrix {
public:
    matrix() = default;

    ~matrix() = default;

    explicit matrix(std::string matrix[]);

    friend const matrix operator+(matrix &left, matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrix_content[i / 3][i % 3] =
                    left.matrix_content[i / 3][i % 3] + right.matrix_content[i / 3][i % 3];
        return result;
    }

    friend const matrix operator-(const matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrix_content[i / 3][i % 3] =
                    left.matrix_content[i / 3][i % 3] - right.matrix_content[i / 3][i % 3];
        return result;
    }

    friend const matrix operator*(const matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                big_integer element(0);
                for (int k = 0; k < 3; ++k) {
                    element += left.matrix_content[i][k] * right.matrix_content[k][j];
                }
                result.matrix_content[i][j] = element;
            }
        }
        return result;
    }

    friend const matrix operator*(const big_integer &bigNum, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrix_content[i / 3][i % 3] = bigNum * right.matrix_content[i / 3][i % 3];
        return result;
    }

    friend const matrix operator~(const matrix &right) {
        matrix result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.matrix_content[i][j] = right.matrix_content[j][i];
        return result;
    }

    friend matrix &operator+=(matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrix_content[i / 3][i % 3] =
                    left.matrix_content[i / 3][i % 3] + right.matrix_content[i / 3][i % 3];
        left = result;
        return left;
    }

    friend matrix &operator-=(matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrix_content[i / 3][i % 3] =
                    left.matrix_content[i / 3][i % 3] - right.matrix_content[i / 3][i % 3];
        left = result;
        return left;
    }

private:
    big_integer matrix_content[3][3];
};


#endif //BIGNUMMATRIX_MATRIX_H
