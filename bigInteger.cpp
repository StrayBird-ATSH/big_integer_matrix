#include "bigInteger.h"
#include <sstream>
#include <stack>

/**
 * Standard constructor of the class.
 * The string argument is directly moved to the field as the construction process.
 * @code{move} method is used to avoid copying and to enhance performance
 * @param number The string representation of the number
 */
bigInteger::bigInteger(std::string number) : number(std::move(number)) {}

/**
 * Getter of the string representation of the number
 * @return The string representation of the number
 */
std::string bigInteger::getNumber() {
    return this->number;
}

/**
 * The method to change the current number's value
 * @param newStr The desired value of the number
 * @return The modified number as a big integer object
 */
bigInteger bigInteger::setNumber(const std::string &newStr) {
    this->number = newStr;
    return *this;
}

/**
 * Detects if the number is a negative number and negates it.
 * @return The modified number as a big integer object
 */
bigInteger bigInteger::negate() {
    if (this->number[0] == '-')
        this->number.erase(0, 1);
    else
        this->number.insert(this->number.begin(), '-');
    return *this;
}

/**
 * The private auxiliary method that trims the leading zeros of the
 * big integer
 * @return The modified number as a big integer object
 */
bigInteger bigInteger::trimLeadingZeros() {
    bigInteger b = *this;
    if (b.number.find_first_not_of('0') != std::string::npos)
        b.setNumber(b.number.erase(0, b.number.find_first_not_of('0')));
    return b;
}

/**
 * The private auxiliary method that decides whether a number is negative
 * @return true if the number is negative and false otherwise
 */
bool bigInteger::isNegative() const {
    return this->number[0] == '-';
}

/**
 * The method is used to output the object as a stream.
 * This function is used in the process of printing this object.
 * @param os Any type of output stream object
 * @param num The big integer object to be output
 * @return The modified stream
 */
std::ostream &operator<<(std::ostream &os, const bigInteger &num) {
    os << num.number;
    return os;
}

/**
 * The implementation of the addition of two big integers.
 * @param lAddend One of the addends
 * @param rAddend One of the addends
 * @return The result of the addition as a big integer object
 */
bigInteger operator+(const bigInteger lAddend, const bigInteger &rAddend) {
    bigInteger b1 = lAddend > rAddend ? lAddend : rAddend, b2 = lAddend > rAddend ? rAddend : lAddend;
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) return (b1.negate() + b2.negate()).negate();
        else if (b1.isNegative() && !b2.isNegative()) return (b1.negate() - b2).negate();
        else return (b2.negate() - b1).negate();
    }
    std::string results;
    int carry = 0, diff = int(b1.number.size() - b2.number.size());
    for (int i = 0; i < diff; ++i) b2.number.insert(b2.number.begin(), '0');
    for (int i = int(b1.number.size() - 1); i >= 0; --i) {
        int sum = (b1.number[i] - '0') + (b2.number[i] - '0') + carry;
        carry = 0;
        if (sum <= 9 || i == 0) results.insert(0, std::to_string(sum));
        else {
            results.insert(0, std::to_string(sum % 10));
            carry = 1;
        }
    }
    return bigInteger(results);
}

/**
 * The implementation method of the subtraction operation.
 * @param minuend The minuend
 * @param subtrahend The subtrahend
 * @return The result of the subtraction as a big integer object
 */
bigInteger operator-(bigInteger minuend, const bigInteger &b) {
    bigInteger subtrahend = b;
    if (minuend.isNegative() || subtrahend.isNegative()) {
        if (minuend.isNegative() && subtrahend.isNegative()) return (minuend.negate() + subtrahend.negate()).negate();
        else if (minuend.isNegative() && !subtrahend.isNegative()) return (minuend.negate() + subtrahend).negate();
        else return subtrahend.negate() + minuend;
    }
    std::string results;
    int n = 0, p = 0;
    bool borrow = false, carryOver = false;
    if (minuend < subtrahend) {
        std::string t = (subtrahend - minuend).negate().getNumber();
        for (unsigned int i = 1; i < t.length(); ++i) {
            if (t[i] != '0') break;
            t.erase(1, 1);
        }
        return bigInteger(t);
    }
    if (minuend.number.size() - subtrahend.getNumber().size() > 1)
        for (unsigned long i = 0; i < minuend.number.size() - subtrahend.getNumber().size() - 1; ++i)
            subtrahend.number.insert(subtrahend.number.begin(), '0');
    int i = int(minuend.number.size() - 1);
    for (int j = int(subtrahend.number.size() - 1); j >= 0; --j) {
        if (((minuend.number[i] - '0') < (subtrahend.number[j] - '0')) && i > 0) {
            n = char((minuend.number[i] - '0') + 10);
            borrow = true;
            if (j > 0 || minuend.number[i - 1] != '0') {
                p = char((minuend.number[i - 1] - '0') - 1);
                if (p == -1) {
                    p = 9;
                    carryOver = true;
                }
                borrow = false;
            }
            if (carryOver) {
                int index = i - 1;
                for (int a = i - 1; (minuend.number[a] - '0') == 0; --a) {
                    minuend.number[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (minuend.number[index] - '0') - 1;
                minuend.number[index] = static_cast<char>(t + '0');
            }
            minuend.number[i - 1] = static_cast<char>(p + '0');
            carryOver = false;
        }
        std::stringstream ss;
        if (((minuend.number[i] - '0') == (subtrahend.number[j] - '0'))) ss << "0";
        else if (n <= 0) ss << ((minuend.number[i] - '0') - (subtrahend.number[j] - '0'));
        else ss << (n - (subtrahend.number[j] - '0'));
        results.insert(0, ss.str());
        --i;
        n = 0;
    }
    if (borrow) {
        std::string number;
        for (int j = minuend.number.length() - subtrahend.number.length() - 1; j >= 0; --j)
            if (minuend.number[j] == '0') {
                number += "0";
                continue;
            } else {
                number.insert(number.begin(), minuend.number[j]);
                int t = strtol(number.c_str(), nullptr, 10);
                --t;
                minuend.number.replace(0, number.size(), std::to_string(t));
                break;
            }
    }
    while (i >= 0) {
        std::stringstream ss;
        if (i == 0) {
            if (minuend.number[i] - '0' != 0) {
                ss << (minuend.number[i] - '0');
                results.insert(0, ss.str());
            }
        } else {
            ss << (minuend.number[i] - '0');
            results.insert(0, ss.str());
        }

        --i;
    }
    if (results.find_first_not_of('0') == std::string::npos) results = "0";
    else if (results[0] == '0') {
        int index = results.find_first_not_of('0');
        results = results.substr(index, results.length() - 1);
    }
    return bigInteger(results);
}

/**
 * The implementation method of the multiplication operation.
 * @param lMultiplier One of the multipliers
 * @param rMultiplier One of the multipliers
 * @return The result of the subtraction as a big integer object
 */
bigInteger operator*(const bigInteger lMultiplier, const bigInteger &rMultiplier) {
    bigInteger b1 = lMultiplier > rMultiplier ? lMultiplier : rMultiplier;
    bigInteger b2 = lMultiplier > rMultiplier ? rMultiplier : lMultiplier;
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) return b1.negate() * b2.negate();
        else if (b1.isNegative() && !b2.isNegative()) return (b1.negate() * b2).negate();
        else return (b2.negate() * b1).negate();
    }
    if (b1 == 0 || b2 == 0) return bigInteger("0");
    int carry = 0;
    int zeroCounter = 0;
    bigInteger b("0");

    for (unsigned int i = 0; i < b1.number.size() - b2.number.size(); ++i)
        b2.number.insert(b2.number.begin(), '0');
    for (long long int i = (b2.number.size() - 1); i >= 0; --i) {
        std::string rr;
        for (long long int j = int(b1.number.size() - 1); j >= 0; --j) {
            int val = ((b2.number[i] - '0') * (b1.number[j] - '0')) + carry;
            carry = 0;
            if (val > 9 && j != 0) {
                carry = val / 10;
                rr.insert(0, std::to_string(val % 10));
            } else rr.insert(0, std::to_string(val));
        }
        if (zeroCounter > 0) for (int x = 0; x < zeroCounter; ++x) rr.append("0");
        ++zeroCounter;
        b += bigInteger(rr);
    }
    if (b.number.find_first_not_of('0') != std::string::npos)
        b.setNumber(b.number.erase(0, b.number.find_first_not_of('0')));
    else b.setNumber("0");
    return b;
}

/**
 * The implementation of determining whether two big integers are equal.
 * The equality of string is used directly for the determination.
 * However, this method assumes that the given two numbers are valid and
 * don't have circumstances like have leading zeros.
 * Considering this method is only used inside this class, further improvement
 * is neglected for the sake of performance.
 * @param n1 One of the numbers
 * @param n2 The other of the numbers
 * @return true if the two numbers are equal and false otherwise
 */
bool operator==(const bigInteger n1, const bigInteger &n2) {
    return n1.number == n2.number;
}

/**
 * The implementation of determining whether one big integer is equal to
 * another native integer.
 * The equality of string is used directly for the determination.
 * However, this method assumes that the given two numbers are valid and
 * don't have circumstances like have leading zeros.
 * Considering this method is only used inside this class, further improvement
 * is neglected for the sake of performance.
 * @param n1 One of the numbers
 * @param n2 The other of the numbers
 * @return true if the two numbers are equal and false otherwise
 */
bool operator==(bigInteger b1, const long long &b2) {
    return b1 == bigInteger(std::to_string(b2));
}

/**
 * The implementation of determining whether one big integer is greater
 * than another big integer
 * @param n1 One of the numbers
 * @param n2 The other of the numbers
 * @return true if the the first number is greater than the second one
 */
bool operator>(bigInteger n1, const bigInteger &n2) {
    if (n1.isNegative() || n2.isNegative()) {
        if (n1.isNegative() && n2.isNegative()) {
            bigInteger bt = n2;
            n1.number.erase(0, 1);
            bt.number.erase(0, 1);
            return n1 < bt;
        } else return !(n1.isNegative() && !n2.isNegative());
    }
    n1 = n1.trimLeadingZeros();
    auto c = bigInteger(n2);
    c = c.trimLeadingZeros();
    if (n1 == c) return false;
    if (n1.number.size() > c.number.size()) return true;
    else if (c.number.size() > n1.number.size()) return false;
    else
        for (unsigned int i = 0; i < n1.number.size(); ++i) {
            if (n1[i] == static_cast<unsigned int>(c.number[i] - '0')) continue;
            return n1[i] > static_cast<unsigned int>(c.number[i] - '0');
        }
    return false;
}

/**
 * The implementation of determining whether one big integer is less
 * than another big integer
 * @param n1 One of the numbers
 * @param n2 The other of the numbers
 * @return true if the the first number is less than the second one
 */
bool operator<(bigInteger &b1, const bigInteger &b2) {
    return !(b1 == b2) && !(b1 > b2);
}

/**
 * The internal auxiliary function that gets the specified bit from
 * a big integer string
 * @param index The index of the desired character
 * @return The character as the actual number
 */
unsigned int bigInteger::operator[](int index) {
    return static_cast<unsigned int>(this->number[index] - '0');
}

/**
 * This overloading operator is not required but its implementation
 * can simplify the codes in other places
 * @param other The addend
 * @return The result of the addition
 */
bigInteger &bigInteger::operator+=(const bigInteger &other) {
    *this = *this + other;
    return *this;
}
