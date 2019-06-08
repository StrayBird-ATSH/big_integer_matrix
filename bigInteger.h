#ifndef BIG_INTEGER_MATRIX_BIGINTEGER_H
#define BIG_INTEGER_MATRIX_BIGINTEGER_H

#include <vector>
#include <string>
#include <iostream>

/**
 * The big integer class that is used to represent a big integer and to
 * perform calculations on big integers.
 *
 * The big integers are stored as a string and the size of the big integer
 * is restricted by the length of the string allowed on the specific operating
 * system. On modern 64 bit operating systems, the length allowed to a string
 * is approximately 2 billion.
 *
 * The operators supported by this class are add, subtract and multiply.
 * However, some other manipulations are currently realized for the sake of
 * internal usage. The three operators are overloading the system operators
 * +, -, and * separately.
 *
 * The constructor of this class allows string argument only. However, for
 * the sake of copy constructors, an empty constructor is also designed.
 *
 * @author Wang, Chen
 * @class bigInteger
 * @date June 4th, 2019
 */
class bigInteger {
public:
    bigInteger() = default;

    explicit bigInteger(std::string number);

    bigInteger &operator+=(const bigInteger &other);

private:
    friend bigInteger operator+(bigInteger b1, const bigInteger &b2);

    friend bigInteger operator-(bigInteger b1, const bigInteger &b2);

    friend bigInteger operator*(bigInteger b1, const bigInteger &b2);

    friend std::ostream &operator<<(std::ostream &os, const bigInteger &num);

    friend bool operator==(bigInteger b1, const bigInteger &b2);

    friend bool operator==(bigInteger b1, const long long &b2);

    friend bool operator<(bigInteger &b1, const bigInteger &b2);

    friend bool operator>(bigInteger b1, const bigInteger &b2);

    unsigned int operator[](int index);

    std::string getNumber();

    bigInteger setNumber(const std::string &newStr);

    bigInteger negate();

    bigInteger trimLeadingZeros();

    bool isNegative() const;

    std::string number;
};

#endif
