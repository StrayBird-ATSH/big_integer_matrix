#include "bigInteger.h"
#include <sstream>
#include <stack>

bigInteger::bigInteger() : _numberString() {}

bigInteger::bigInteger(std::string number) : _numberString(number) {}

bigInteger::bigInteger(long long number) : _numberString(std::to_string(number)) {}

std::string bigInteger::getString() {
    return this->_numberString;
}

bigInteger bigInteger::setString(const std::string &newStr) {
    this->_numberString = newStr;
    return *this;
}

bigInteger bigInteger::negate() {
    if (this->_numberString[0] == '-')
        this->_numberString.erase(0, 1);
    else
        this->_numberString.insert(this->_numberString.begin(), '-');
    return *this;
}

bigInteger bigInteger::trimLeadingZeros() {
    bigInteger b = *this;
    if (b._numberString.find_first_not_of('0') != std::string::npos)
        b.setString(b._numberString.erase(0, b._numberString.find_first_not_of('0')));
    return b;
}

bool bigInteger::equals(const bigInteger &other) {
    return this->_numberString == other._numberString;
}

bool bigInteger::equals(const long long &other) {
    return this->getString() == std::to_string(other);
}

bool bigInteger::isNegative() const {
    return this->_numberString[0] == '-';
}

std::ostream &operator<<(std::ostream &os, const bigInteger &num) {
    os << num._numberString;
    return os;
}

bigInteger operator+(const bigInteger b4, const bigInteger &b3) {
    bigInteger b1 = b4 > b3 ? b4 : b3;
    bigInteger b2 = b4 > b3 ? b3 : b4;
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) return (b1.negate() + b2.negate()).negate();
        else if (b1.isNegative() && !b2.isNegative()) return (b1.negate() - b2).negate();
        else return (b2.negate() - b1).negate();
    }
    std::string results;
    int carry = 0;
    int diff = int(b1._numberString.size() - b2._numberString.size());
    for (int i = 0; i < diff; ++i) b2._numberString.insert(b2._numberString.begin(), '0');
    for (int i = int(b1._numberString.size() - 1); i >= 0; --i) {
        int sum = (b1._numberString[i] - '0') + (b2._numberString[i] - '0') + carry;
        carry = 0;
        if (sum <= 9 || i == 0) results.insert(0, std::to_string(sum));
        else {
            results.insert(0, std::to_string(sum % 10));
            carry = 1;
        }
    }
    return bigInteger(results);
}

bigInteger operator-(bigInteger b3, const bigInteger &b4) {
    bigInteger b1 = b3, b2 = b4;
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) return (b1.negate() + b2.negate()).negate();
        else if (b1.isNegative() && !b2.isNegative()) return (b1.negate() + b2).negate();
        else return b2.negate() + b1;
    }
    std::string results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if (b1 < b2) {
        //Negative answer
        std::string t = (b2 - b1).negate().getString();
        for (unsigned int i = 1; i < t.length(); ++i) {
            if (t[i] != '0') break;
            t.erase(1, 1);
        }
        return bigInteger(t);
    }

    //This next if-block fixes the case where the digit difference is greater than 1
    //100 - 5 is an example. This code adds 0's to make it, for example, 100 - 05, which
    //allows the rest of the subtraction code to work.
    if (b1._numberString.size() - b2.getString().size() > 1)
        for (unsigned long i = 0; i < b1._numberString.size() - b2.getString().size() - 1; ++i)
            b2._numberString.insert(b2._numberString.begin(), '0');
    int i = int(b1._numberString.size() - 1);
    for (int j = int(b2._numberString.size() - 1); j >= 0; --j) {
        if (((b1._numberString[i] - '0') < (b2._numberString[j] - '0')) && i > 0) {
            n = char((b1._numberString[i] - '0') + 10);
            takeOffOne = true;
            if (j > 0 || b1._numberString[i - 1] != '0') {
                p = char((b1._numberString[i - 1] - '0') - 1);
                if (p == -1) {
                    p = 9;
                    shouldBeTen = true;
                }
                takeOffOne = false;
            }
            if (shouldBeTen) {
                int index = i - 1;
                for (int a = i - 1; (b1._numberString[a] - '0') == 0; --a) {
                    b1._numberString[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (b1._numberString[index] - '0') - 1;
                b1._numberString[index] = static_cast<char>(t + '0');
            }
            b1._numberString[i - 1] = static_cast<char>(p + '0');
            shouldBeTen = false;
        }
        std::stringstream ss;
        if (((b1._numberString[i] - '0') == (b2._numberString[j] - '0'))) ss << "0";
        else if (n <= 0) ss << ((b1._numberString[i] - '0') - (b2._numberString[j] - '0'));
        else ss << (n - (b2._numberString[j] - '0'));
        results.insert(0, ss.str());
        --i;
        n = 0;
    }
    if (takeOffOne) {
        std::string number;
        for (int j = b1._numberString.length() - b2._numberString.length() - 1; j >= 0; --j)
            if (b1._numberString[j] == '0') {
                number += "0";
                continue;
            } else {
                number.insert(number.begin(), b1._numberString[j]);
                int t = strtol(number.c_str(), nullptr, 10);
                --t;
                b1._numberString.replace(0, number.size(), std::to_string(t));
                break;
            }
    }
    while (i >= 0) {
        std::stringstream ss;
        if (i == 0) {
            if (b1._numberString[i] - '0' != 0) {
                ss << (b1._numberString[i] - '0');
                results.insert(0, ss.str());
            }
        } else {
            ss << (b1._numberString[i] - '0');
            results.insert(0, ss.str());
        }

        --i;
    }
    //In the case of all 0's, we only want to return one of them
    if (results.find_first_not_of('0') == std::string::npos) {
        results = "0";
    } else if (results[0] == '0') {
        int index = results.find_first_not_of('0');
        results = results.substr(index, results.length() - 1);
    }
    return bigInteger(results);
}

bigInteger operator*(bigInteger b3, const bigInteger &b4) {
    bigInteger b1 = b3 > b4 ? b3 : b4;
    bigInteger b2 = b3 > b4 ? b4 : b3;
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) return b1.negate() * b2.negate();
        else if (b1.isNegative() && !b2.isNegative()) return (b1.negate() * b2).negate();
        else return (b2.negate() * b1).negate();
    }
    if (b1 == 0 || b2 == 0) return 0;
    int carry = 0;
    int zeroCounter = 0;
    bigInteger b = 0;

    for (unsigned int i = 0; i < b1._numberString.size() - b2._numberString.size(); ++i)
        b2._numberString.insert(b2._numberString.begin(), '0');
    for (long long int i = (b2._numberString.size() - 1); i >= 0; --i) {
        std::string rr;
        for (long long int j = int(b1._numberString.size() - 1); j >= 0; --j) {
            int val = ((b2._numberString[i] - '0') * (b1._numberString[j] - '0')) + carry;
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
    if (b._numberString.find_first_not_of('0') != std::string::npos)
        b.setString(b._numberString.erase(0, b._numberString.find_first_not_of('0')));
    else
        //In the case of all 0's, we only want to return one of them
        b.setString("0");
    return b;
}

bool operator==(bigInteger b1, const bigInteger &b2) {
    return b1.equals(b2);
}

bool operator==(bigInteger b1, const long long &b2) {
    return b1.equals(b2);
}

bool operator>(bigInteger b1, const bigInteger &b2) {
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) {
            bigInteger bt = b2;
            b1._numberString.erase(0, 1);
            bt._numberString.erase(0, 1);
            return b1 < bt;
        } else return !(b1.isNegative() && !b2.isNegative());
    }
    b1 = b1.trimLeadingZeros();
    auto c = bigInteger(b2);
    c = c.trimLeadingZeros();
    if (b1 == c) return false;
    if (b1._numberString.size() > c._numberString.size()) return true;
    else if (c._numberString.size() > b1._numberString.size()) return false;
    else
        for (unsigned int i = 0; i < b1._numberString.size(); ++i) {
            if (b1[i] == static_cast<unsigned int>(c._numberString[i] - '0')) continue;
            return b1[i] > static_cast<unsigned int>(c._numberString[i] - '0');
        }
    return false;
}

bool operator<(bigInteger &b1, const bigInteger &b2) {
    return !(b1 == b2) && !(b1 > b2);
}

unsigned int bigInteger::operator[](int index) {
    if (this->_numberString[index] == '-') std::cerr << "You cannot get the negative sign from the number" << std::endl;
    return static_cast<unsigned int>(this->_numberString[index] - '0');
}

bigInteger &bigInteger::operator=(const bigInteger &other) = default;

bigInteger &bigInteger::operator+=(const bigInteger &other) {
    *this = *this + other;
    return *this;
}
