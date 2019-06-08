#ifndef BIG_NUM_MATRIX_H
#define BIG_NUM_MATRIX_H

#include "bigInteger.h"
#include <map>

/**
 * The matrix class is designed to represent a 3 by 3 matrix whose
 * elements are big integers. The big integer implementation relies
 * on the big integer class in this project. The maximal length of the
 * big integers depend on the length allowed for the strings on a system
 * The matrix class support the same operations as the big integers.
 *
 * The operators supported by this class are add, subtract and multiply.
 * However, some other manipulations are currently realized for the sake of
 * internal usage. The three operators are overloading the system operators
 * +, -, and * separately.
 * It should be noted that * operator has two different functions. They are
 * matrix multiply matrix and big integer multiply matrix separately.
 *
 * The constructor of this class allows string array argument only. However, for
 * the sake of copy constructors, an empty constructor is also designed.
 *
 * @author Wang, Chen
 * @class matrix
 * @date June 4th, 2019
 */
class matrix {
public:
    matrix() = default;

    ~matrix() = default;

    explicit matrix(std::string matrix[]);

    friend const matrix operator+(matrix &left, matrix &right);

    friend const matrix operator-(const matrix &left, const matrix &right);

    friend const matrix operator*(const matrix &left, const matrix &right);

    friend const matrix operator*(const bigInteger &bigNum, const matrix &right);

    friend const matrix operator~(const matrix &right);

    friend matrix &operator+=(matrix &left, const matrix &right);

    friend matrix &operator-=(matrix &left, const matrix &right);

    friend std::ostream &operator<<(std::ostream &stream, const matrix &matrix1);

private:
    bigInteger matrixContent[3][3];
};

matrix eval(std::string expression, const std::map<std::string, matrix> &map);

#endif //BIG_NUM_MATRIX_H
