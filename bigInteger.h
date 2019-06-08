#ifndef BIG_INTEGER_MATRIX_BIGINTEGER_H
#define BIG_INTEGER_MATRIX_BIGINTEGER_H

#include <vector>
#include <string>
#include <iostream>

class bigInteger {
public:
    bigInteger();

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

    std::string getString();

    bigInteger setString(const std::string &newStr);

    bigInteger negate();

    bigInteger trimLeadingZeros();

    bool equals(const long long &other);

    bool isNegative() const;

    std::string number;
};

#endif
