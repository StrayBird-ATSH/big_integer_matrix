/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Mark Guerra
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <string>
#include <iostream>

/**
 * BigNumber class
 */
class big_integer {
public:

    big_integer();

    //@{
    /**
     * BigNumber constructor
     * @param number - The initial value of the BigNumber
     */
    big_integer(std::string number);

    big_integer(long long number);
    //@}

    /**
     * Add another BigNumber to the current instance
     * @param other - The other BigNumber
     * @return The sum of the two BigNumbers
     */
    big_integer add(big_integer other);

    /**
     * Subtract another BigNumber from the current instance
     * @param other - The other BigNumber
     * @return The difference of the two BigNumbers
     */
    big_integer subtract(big_integer other);

    /**
     * Multiply the current instance by another BigNumber
     * @param other - The other BigNumber
     * @return The product of the two BigNumbers
     */
    big_integer multiply(big_integer other);

    /**
     * Divide the current instance by another BigNumber
     * @param other - The other BigNumber
     * @return The quotient of the two BigNumbers
     */
    big_integer divide(big_integer other);

    /**
     * Raise the current instance to the power of an exponent
     * @param exponent - The power to be raised by
     * @return - The resulting BigNumber after exponentiation
     */
    big_integer pow(int exponent);

    /**
     * Get the string value of the current instance
     * @return The BigNumber as a string
     */
    std::string getString();

    /**
     * Set the value of the current instance with a string
     * @param newStr - The new value for the BigNumber
     * @return The BigNumber with the new value
     */
    big_integer setString(const std::string &newStr);

    /**
     * Negates the current instance
     * @return The BigNumber after negation
     */
    big_integer negate();

    big_integer trimLeadingZeros();

    //@{
    /**
     * Check if another BigNumber is equal to the current instance
     * @param other - The other BigNumber
     * @return True if equal, otherwise false
     */
    bool equals(const big_integer &other);

    bool equals(const long long &other);

    bool equals(const std::string &other);
    //@}

    /**
     * Get the number of digits in the current instance
     * @return The number of digits
     */
    unsigned int digits();

    /**
     * Get whether or not the current instance is a negative number
     * @return True if negative, otherwise false
     */
    bool isNegative() const;

    /**
     * Get whether or not the current instance is a positive number
     * @return True if positive, otherwise false
     */
    bool isPositive();

    /**
     * Get whether or not the current instance is an even number
     * @return True if even, otherwise false
     */
    bool isEven();

    /**
     * Get whether or not the current instance is an odd number
     * @return True if odd, otherwise false
     */
    bool isOdd();

    /**
     * Get the absolute value of the current instance
     * @return The absolute value of the BigNumber
     */
    big_integer abs() const;

    /**
     * Output stream operator
     * @param os The output stream
     * @param num The current instance
     * @return The output stream with the current instance
     */
    friend std::ostream &operator<<(std::ostream &os, const big_integer &num);

    //@{
    /**
     * Addition operator
     * @param b1 - The current instance
     * @param b2 - The number being added
     * @return The sum of the two numbers
     */
    friend big_integer operator+(big_integer b1, const big_integer &b2);

    friend big_integer operator+(big_integer b1, const long long &b2);

    friend big_integer operator+(big_integer b1, const std::string &b2);
    //@}

    //@{
    /**
     * Subtraction operator
     * @param b1 - The current instance
     * @param b2 - The number being subtracted
     * @return The difference of the two numbers
     */
    friend big_integer operator-(big_integer b1, const big_integer &b2);

    friend big_integer operator-(big_integer b1, const long long &b2);

    friend big_integer operator-(big_integer b1, const std::string &b2);
    //@}

    //@{
    /**
     * Multiplication operator
     * @param b1 - The current instance
     * @param b2 - The number being multiplied by
     * @return The product of the two numbers
     */
    friend big_integer operator*(big_integer b1, const big_integer &b2);

    friend big_integer operator*(big_integer b1, const long long &b2);

    friend big_integer operator*(big_integer b1, const std::string &b2);
    //@}

    //@{
    /**
     * Division operator
     * @param b1 - The current instance
     * @param b2 - The number being divided by
     * @return The quotient of the two numbers
     */
    friend big_integer operator/(big_integer b1, const big_integer &b2);

    friend big_integer operator/(big_integer b1, const long long &b2);

    friend big_integer operator/(big_integer b1, const std::string &b2);
    //@}

    /**
     * Exponent operator
     * @param b1 - The current instance
     * @param b2 - The exponent
     * @return The value after exponentiation
     */
    friend big_integer operator^(big_integer b1, const int &b2);

    //@{
    /**
     * Equality operator
     * @param b1 - The current instance
     * @param b2 - Another value
     * @return True if equal, otherwise false
     */
    friend bool operator==(big_integer b1, const big_integer &b2);

    friend bool operator==(big_integer b1, const long long &b2);

    friend bool operator==(big_integer b1, const std::string &b2);
    //@}

    /**
     * Greater-than operator
     * @param b1 - The current instance
     * @param b2 - Another BigNumber
     * @return True if current instance is greater, otherwise false
     */
    friend bool operator>(big_integer b1, const big_integer &b2);

    /**
     * Less-than operator
     * @param b1 - The current instance
     * @param b2 - Another BigNumber
     * @return True if current instance is less, otherwise false
     */
    friend bool operator<(big_integer b1, const big_integer &b2);

    /**
     * Greater-than or equal-to operator
     * @param b1 - The current instance
     * @param b2 - Another BigNumber
     * @return True if current instance is greater or equal, otherwise false
     */
    friend bool operator>=(big_integer b1, const big_integer &b2);

    /**
     * Less-than or equal-to operator
     * @param b1 - The current instance
     * @param b2 - Another BigNumber
     * @return True if current instance is less or equal, otherwise false
     */
    friend bool operator<=(big_integer b1, const big_integer &b2);

    //@{
    /**
     * Assignment operator
     * @param other - The new value for the BigNumber
     * @return A BigNumber containing the new value
     */
    big_integer &operator=(const big_integer &other);

    big_integer &operator=(const long long &other);

    big_integer &operator=(const std::string &other);
    //@}

    //@{
    /**
     * Addition assignment operator\n
     * Adds and assigns a value to the current instance
     * @param other - The value being added
     * @return The new value after addition and assignment
     */
    big_integer &operator+=(const big_integer &other);

    big_integer &operator+=(const long long &other);

    big_integer &operator+=(const std::string &other);
    //@}

    //@{
    /**
     * Subtraction assignment operator\n
     * Subtracts and assigns a value to the current instance
     * @param other - The value being subtracted
     * @return The new value after subtraction and assignment
     */
    big_integer &operator-=(const big_integer &other);

    big_integer &operator-=(const long long &other);

    big_integer &operator-=(const std::string &other);
    //@}

    //@{
    /**
     * Multiplication assignment operator\n
     * Multiplies and assigns a value to the current instance
     * @param other - The value being multiplied
     * @return The new value after multiplication and assignment
     */
    big_integer &operator*=(const big_integer &other);

    big_integer &operator*=(const long long &other);

    big_integer &operator*=(const std::string &other);
    //@}

    //@{
    /**
     * Division assignment operator\n
     * Divides and assigns a value to the current instance
     * @param other - The value being divided
     * @return The new value after division and assignment
     */
    big_integer &operator/=(const big_integer &other);

    big_integer &operator/=(const long long &other);

    big_integer &operator/=(const std::string &other);
    //@}

    /**
     * Pre-increment operator
     * @return The incremented BigNumber
     */
    big_integer &operator++();

    /**
     * Pre-decrement operator
     * @return The decremented BigNumber
     */
    big_integer &operator--();

    /**
     * Post-increment operator
     * @return The incremented BigNumber
     */
    big_integer operator++(int);

    /**
     * Post-decrement operator
     * @return The decremented BigNumber
     */
    big_integer operator--(int);

    /**
     * The index operator
     * @param index The position being looked at
     * @return The number at the specified position in the BigNumber string
     */
    unsigned int operator[](int index);

private:
    std::string _numberString;      //The big number represented as a string

    //Methods
    big_integer addll(const long long &other);

    big_integer addstr(const std::string &other);

    big_integer subtractll(const long long &other);

    big_integer subtractstr(const std::string &other);

    big_integer multiplyll(const long long &other);

    big_integer multiplystr(const std::string &other);

    big_integer dividell(const long long &other);

    big_integer dividestr(const std::string &other);
};


#endif
