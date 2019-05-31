//
// Created by zhang on 5/31/2019.
//

#ifndef BIGNUMMATRIX_MATRIX_H
#define BIGNUMMATRIX_MATRIX_H

#include "big_integer.h"
#include <string>

class matrix {
public:
    matrix();

    explicit matrix(std::string matrix[]);

    friend const matrix operator+(matrix &left, matrix &right) {
        matrix result;
//        result.matrix_content =
//                {
//                        {&(*left.matrix_content[0][0] + *left.matrix_content[0][0]),
//                        }
//                };

        return result;
    }

    friend const matrix operator-(const matrix &left, const matrix &right);

    friend const big_integer operator*(const matrix &left, const matrix &right);

    friend const matrix operator*(const big_integer &bigNum, const matrix &matrix);

    friend const matrix operator~(const matrix &matrix);

    friend matrix &operator+=(matrix &left, const matrix &right);

    friend matrix &operator-=(matrix &left, const matrix &right);


private:
    big_integer *matrix_content[3][3];
};


#endif //BIGNUMMATRIX_MATRIX_H
