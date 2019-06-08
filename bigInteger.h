#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <string>
#include <iostream>

/**
 * BigNumber class
 */
class bigInteger {
public:
    //@{
    /**
     * BigNumber constructor
     * @param number - The initial value of the BigNumber
     */
    bigInteger();

    explicit bigInteger(std::string number);

    bigInteger(long long number);
    //@}

    /**
     * Subtract another BigNumber from the current instance
     * @param other - The other BigNumber
     * @return The difference of the two BigNumbers
     */
    bigInteger subtract(bigInteger other);

    /**
     * Multiply the current instance by another BigNumber
     * @param other - The other BigNumber
     * @return The product of the two BigNumbers
     */
    bigInteger multiply(bigInteger other);

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
    bigInteger setString(const std::string &newStr);

    /**
     * Negates the current instance
     * @return The BigNumber after negation
     */
    bigInteger negate();

    bigInteger trimLeadingZeros();

    //@{
    /**
     * Check if another BigNumber is equal to the current instance
     * @param other - The other BigNumber
     * @return True if equal, otherwise false
     */
    bool equals(const bigInteger &other);

    bool equals(const long long &other);
    //@}

    /**
     * Get whether or not the current instance is a negative number
     * @return True if negative, otherwise false
     */
    bool isNegative() const;

    /**
     * Output stream operator
     * @param os The output stream
     * @param num The current instance
     * @return The output stream with the current instance
     */
    friend std::ostream &operator<<(std::ostream &os, const bigInteger &num);

    //@{
    /**
     * Addition operator
     * @param b1 - The current instance
     * @param b2 - The number being added
     * @return The sum of the two numbers
     */
    friend bigInteger operator+(bigInteger b1, const bigInteger &b2);
    //@}

    //@{
    /**
     * Subtraction operator
     * @param b1 - The current instance
     * @param b2 - The number being subtracted
     * @return The difference of the two numbers
     */
    friend bigInteger operator-(bigInteger b1, const bigInteger &b2);
    //@}

    //@{
    /**
     * Multiplication operator
     * @param b1 - The current instance
     * @param b2 - The number being multiplied by
     * @return The product of the two numbers
     */
    friend bigInteger operator*(bigInteger b1, const bigInteger &b2);
    //@}

    //@{
    /**
     * Equality operator
     * @param b1 - The current instance
     * @param b2 - Another value
     * @return True if equal, otherwise false
     */
    friend bool operator==(bigInteger b1, const bigInteger &b2);

    friend bool operator==(bigInteger b1, const long long &b2);
    //@}

    /**
     * Greater-than operator
     * @param b1 - The current instance
     * @param b2 - Another BigNumber
     * @return True if current instance is greater, otherwise false
     */
    friend bool operator>(bigInteger b1, const bigInteger &b2);

    /**
     * Less-than operator
     * @param b1 - The current instance
     * @param b2 - Another BigNumber
     * @return True if current instance is less, otherwise false
     */
    friend bool operator<(bigInteger &b1, const bigInteger &b2);

    //@{
    /**
     * Assignment operator
     * @param other - The new value for the BigNumber
     * @return A BigNumber containing the new value
     */
    bigInteger &operator=(const bigInteger &other);

    //@}

    //@{
    /**
     * Addition assignment operator\n
     * Adds and assigns a value to the current instance
     * @param other - The value being added
     * @return The new value after addition and assignment
     */
    bigInteger &operator+=(const bigInteger &other);
    //@}

    /**
     * The index operator
     * @param index The position being looked at
     * @return The number at the specified position in the BigNumber string
     */
    unsigned int operator[](int index);

private:
    std::string _numberString;      //The big number represented as a string
};

#endif
