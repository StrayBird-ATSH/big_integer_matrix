#include "bigInteger.h"
#include <sstream>
#include <stack>

bigInteger::bigInteger() : number() {}

bigInteger::bigInteger(std::string number) : number(std::move(number)) {}

std::string bigInteger::getString() {
    return this->number;
}

bigInteger bigInteger::setString(const std::string &newStr) {
    this->number = newStr;
    return *this;
}

bigInteger bigInteger::negate() {
    if (this->number[0] == '-')
        this->number.erase(0, 1);
    else
        this->number.insert(this->number.begin(), '-');
    return *this;
}

bigInteger bigInteger::trimLeadingZeros() {
    bigInteger b = *this;
    if (b.number.find_first_not_of('0') != std::string::npos)
        b.setString(b.number.erase(0, b.number.find_first_not_of('0')));
    return b;
}

bool bigInteger::equals(const long long &other) {
    return this->getString() == std::to_string(other);
}

bool bigInteger::isNegative() const {
    return this->number[0] == '-';
}

std::ostream &operator<<(std::ostream &os, const bigInteger &num) {
    os << num.number;
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
    int diff = int(b1.number.size() - b2.number.size());
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
        std::string t = (b2 - b1).negate().getString();
        for (unsigned int i = 1; i < t.length(); ++i) {
            if (t[i] != '0') break;
            t.erase(1, 1);
        }
        return bigInteger(t);
    }
    if (b1.number.size() - b2.getString().size() > 1)
        for (unsigned long i = 0; i < b1.number.size() - b2.getString().size() - 1; ++i)
            b2.number.insert(b2.number.begin(), '0');
    int i = int(b1.number.size() - 1);
    for (int j = int(b2.number.size() - 1); j >= 0; --j) {
        if (((b1.number[i] - '0') < (b2.number[j] - '0')) && i > 0) {
            n = char((b1.number[i] - '0') + 10);
            takeOffOne = true;
            if (j > 0 || b1.number[i - 1] != '0') {
                p = char((b1.number[i - 1] - '0') - 1);
                if (p == -1) {
                    p = 9;
                    shouldBeTen = true;
                }
                takeOffOne = false;
            }
            if (shouldBeTen) {
                int index = i - 1;
                for (int a = i - 1; (b1.number[a] - '0') == 0; --a) {
                    b1.number[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (b1.number[index] - '0') - 1;
                b1.number[index] = static_cast<char>(t + '0');
            }
            b1.number[i - 1] = static_cast<char>(p + '0');
            shouldBeTen = false;
        }
        std::stringstream ss;
        if (((b1.number[i] - '0') == (b2.number[j] - '0'))) ss << "0";
        else if (n <= 0) ss << ((b1.number[i] - '0') - (b2.number[j] - '0'));
        else ss << (n - (b2.number[j] - '0'));
        results.insert(0, ss.str());
        --i;
        n = 0;
    }
    if (takeOffOne) {
        std::string number;
        for (int j = b1.number.length() - b2.number.length() - 1; j >= 0; --j)
            if (b1.number[j] == '0') {
                number += "0";
                continue;
            } else {
                number.insert(number.begin(), b1.number[j]);
                int t = strtol(number.c_str(), nullptr, 10);
                --t;
                b1.number.replace(0, number.size(), std::to_string(t));
                break;
            }
    }
    while (i >= 0) {
        std::stringstream ss;
        if (i == 0) {
            if (b1.number[i] - '0' != 0) {
                ss << (b1.number[i] - '0');
                results.insert(0, ss.str());
            }
        } else {
            ss << (b1.number[i] - '0');
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

bigInteger operator*(bigInteger b3, const bigInteger &b4) {
    bigInteger b1 = b3 > b4 ? b3 : b4;
    bigInteger b2 = b3 > b4 ? b4 : b3;
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
        b.setString(b.number.erase(0, b.number.find_first_not_of('0')));
    else b.setString("0");
    return b;
}

bool operator==(bigInteger b1, const bigInteger &b2) {
    return b1.number == b2.number;
}

bool operator==(bigInteger b1, const long long &b2) {
    return b1.equals(b2);
}

bool operator>(bigInteger b1, const bigInteger &b2) {
    if (b1.isNegative() || b2.isNegative()) {
        if (b1.isNegative() && b2.isNegative()) {
            bigInteger bt = b2;
            b1.number.erase(0, 1);
            bt.number.erase(0, 1);
            return b1 < bt;
        } else return !(b1.isNegative() && !b2.isNegative());
    }
    b1 = b1.trimLeadingZeros();
    auto c = bigInteger(b2);
    c = c.trimLeadingZeros();
    if (b1 == c) return false;
    if (b1.number.size() > c.number.size()) return true;
    else if (c.number.size() > b1.number.size()) return false;
    else
        for (unsigned int i = 0; i < b1.number.size(); ++i) {
            if (b1[i] == static_cast<unsigned int>(c.number[i] - '0')) continue;
            return b1[i] > static_cast<unsigned int>(c.number[i] - '0');
        }
    return false;
}

bool operator<(bigInteger &b1, const bigInteger &b2) {
    return !(b1 == b2) && !(b1 > b2);
}

unsigned int bigInteger::operator[](int index) {
    if (this->number[index] == '-') std::cerr << "You cannot get the negative sign from the number" << std::endl;
    return static_cast<unsigned int>(this->number[index] - '0');
}

bigInteger &bigInteger::operator+=(const bigInteger &other) {
    *this = *this + other;
    return *this;
}
