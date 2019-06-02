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

    matrix(matrix &originalMatrix);

    explicit matrix(std::string matrix[]);

    friend const matrix operator+(matrix &left, matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrixContent[i / 3][i % 3] =
                    left.matrixContent[i / 3][i % 3] + right.matrixContent[i / 3][i % 3];
        return result;
    }

    friend const matrix operator-(const matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrixContent[i / 3][i % 3] =
                    left.matrixContent[i / 3][i % 3] - right.matrixContent[i / 3][i % 3];
        return result;
    }

    friend const matrix operator*(const matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                big_integer element(0);
                for (int k = 0; k < 3; ++k) {
                    element += left.matrixContent[i][k] * right.matrixContent[k][j];
                }
                result.matrixContent[i][j] = element;
            }
        }
        return result;
    }

    friend const matrix operator*(const big_integer &bigNum, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrixContent[i / 3][i % 3] = bigNum * right.matrixContent[i / 3][i % 3];
        return result;
    }

    friend const matrix operator~(const matrix &right) {
        matrix result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.matrixContent[i][j] = right.matrixContent[j][i];
        return result;
    }

    friend matrix &operator+=(matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrixContent[i / 3][i % 3] =
                    left.matrixContent[i / 3][i % 3] + right.matrixContent[i / 3][i % 3];
        left = result;
        return left;
    }

    friend matrix &operator-=(matrix &left, const matrix &right) {
        matrix result;
        for (int i = 0; i < 9; ++i)
            result.matrixContent[i / 3][i % 3] =
                    left.matrixContent[i / 3][i % 3] - right.matrixContent[i / 3][i % 3];
        left = result;
        return left;
    }

private:
    big_integer matrixContent[3][3];
};


#endif //BIGNUMMATRIX_MATRIX_H
