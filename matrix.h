//
// Created by zhang on 5/31/2019.
//

#ifndef BIGNUMMATRIX_MATRIX_H
#define BIGNUMMATRIX_MATRIX_H

#include "big_integer.h"
#include <string>
#include <map>

class matrix {
public:
    matrix() = default;

    ~matrix() = default;

    explicit matrix(std::string matrix[]);

    friend const matrix operator+(matrix &left, matrix &right);

    friend const matrix operator-(const matrix &left, const matrix &right);

    friend const matrix operator*(const matrix &left, const matrix &right);

    friend const matrix operator*(const big_integer &bigNum, const matrix &right);

    friend const matrix operator~(const matrix &right);

    friend matrix &operator+=(matrix &left, const matrix &right);

    friend matrix &operator-=(matrix &left, const matrix &right);

    friend std::ostream &operator<<(std::ostream &stream, const matrix &matrix1);

private:
    big_integer matrixContent[3][3];
};

matrix computeExpression(const std::map<std::string, matrix> &map, const std::string &expression);

matrix computeExpression1(std::string expression, const std::map<std::string, matrix> &map);

#endif //BIGNUMMATRIX_MATRIX_H
