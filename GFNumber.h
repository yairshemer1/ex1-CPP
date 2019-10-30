//
// Created by Yair Shemer on 27/08/2019.
//

#ifndef EX1_GFNUMBER_H
#define EX1_GFNUMBER_H

#include "GField.h"

/**
 * A class representing a number in a galois field. The class includes all arithmetic functions
 * and prime factors analysis.
 */
class GFNumber
{
private:
    GField _gf; // the galois field of the number
    long _n; // the number

    /**
     * A function to create a number in the field from a given number
     * @param n the given number
     * @return the number in the field
     */
    long _calcModulo(long n);

    /**
     * A function to manage the list memory allocations, including deleting and returning a
     * bigger array
     * @param arr the older array
     * @param counter reference to control on how many objects in the array at the moment
     * @param last the GFNumber to enter the last cell of the array
     * @return the bigger array
     */
    static GFNumber *_expandArray(GFNumber *arr, int &counter, const GFNumber &last);

    /**
     * A function x^2 +1
     * @param x a GFNumber
     * @param mod the modulo
     * @return the result
     */
    static GFNumber _f(const GFNumber &x, const long mod);

    /**
     * An algorithm that is supposed to calculate factors of a given number
     * @return a GFNumber that divides the current number
     */
    GFNumber _pollardRho();

    /**
     * A function to add a given list the current GFNumber.
     * @param currentList the list before adding to is the current GFNumber
     * @param counter reference to a counter, the size of the array
     * @return A list of GFNumber including current number and older list
     */
    GFNumber *_bruteForce(GFNumber *currentList, int &counter);

public:

    /**
     * Default constructor. Initializes the field values as it's default, and the number to 0.
     */
    GFNumber();

    /**
     * A constructor that initializes the field as it's default and the number to the given n.
     * @param n the number
     */
    GFNumber(long n);

    /**
     * A constructor given both field value and n value.
     * @param n the number
     * @param gf the field
     */
    GFNumber(long n, const GField &gf);

    /**
     * A copy constructor
     * @param other the GFNumber to copy
     */
    GFNumber(const GFNumber &other);

    /**
     * Returns the number of the GFNumber
     * @return the number
     */
    long getNumber() const;

    /**
     * Returns the field of the GFNumber
     * @return the field
     */
    GField getField() const;

    /**
     * A function to calculate a list of all prime factors creating the GFNumber
     * @param counter counts the amount of factors
     * @return the list of prime factors
     */
    GFNumber *getPrimeFactors(int *counter);

    /**
     * A function to print the list returned from getPrimeFactors. It will allocate memory and
     * free it itself.
     */
    void printFactors();

    /**
     * A function to check if the GFNumber is a prime number
     * @return true for prime, false otherwise
     */
    bool getIsPrime();

    /**
     * Overriding the = operator - default
     * @param other the object to assign
     * @return the assigned object
     */
    GFNumber &operator=(const GFNumber &other) = default;

    /**
     * Overriding the == operator
     * @param other the object to compare with
     * @return true for equality, false otherwise
     */
    bool operator==(const GFNumber &other) const;

    /**
     * Overriding the != operator
     * @param other the object to compare with
     * @return true for inequality, false otherwise
     */
    bool operator!=(const GFNumber &other) const;

    /**
     * Overriding the + operator
     * @param other object as a GFNumber
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator+(const GFNumber &other) const;

    /**
     * Overriding the + operator
     * @param other object as a long
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator+(const long &other) const;

    /**
     * Overriding the += operator
     * @param other object as a GFNumber
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber &operator+=(const GFNumber &other);

    /**
     * Overriding the += operator
     * @param other object as a long
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber &operator+=(const long &other);

    /**
     * Overriding the - operator
     * @param other object as a GFNumber
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator-(const GFNumber &other) const;

    /**
     * Overriding the - operator
     * @param other object as a long
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator-(const long &other) const;

    /**
     * Overriding the -= operator
     * @param other object as a GFNumber
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber operator-=(const GFNumber &other);

    /**
     * Overriding the -= operator
     * @param other object as a long
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber &operator-=(const long &other);

    /**
     * Overriding the * operator
     * @param other object as a GFNumber
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator*(const GFNumber &other) const;

    /**
     * Overriding the * operator
     * @param other object as a long
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator*(const long &other) const;

    /**
     * Overriding the *= operator
     * @param other object as a GFNumber
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber operator*=(const GFNumber &other);

    /**
     * Overriding the *= operator
     * @param other object as a long
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber &operator*=(const long &other);

    /**
     * Overriding the % operator
     * @param other object as a GFNumber
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator%(const GFNumber &other) const;

    /**
     * Overriding the % operator
     * @param other object as a long
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator%(const long &other) const;

    /**
     * Overriding the %= operator
     * @param other object as a GFNumber
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber operator%=(const GFNumber &other);

    /**
     * Overriding the %= operator
     * @param other object as a long
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber &operator%=(const long &other);

    /**
     * Overriding the / operator
     * @param other object as a GFNumber
     * @return A new GFNumber with the correct arithmetic action
     */
    GFNumber operator/(const GFNumber &other) const;

    /**
     * Overriding the /= operator
     * @param other object as a GFNumber
     * @return A reference to the same GFNumber with the correct arithmetic action
     */
    GFNumber &operator/=(const GFNumber &other);

    /**
     * Overriding the > operator
     * @param other object to compare with
     * @return true if the GFNumber is bigger than other, false otherwise
     */
    bool operator>(const GFNumber &other) const;

    /**
     * Overriding the < operator
     * @param other object to compare with
     * @return true if the GFNumber is smaller than other, false otherwise
     */
    bool operator<(const GFNumber &other) const;

    /**
     * Overriding the >= operator
     * @param other object to compare with
     * @return true if the GFNumber is bigger than or equals to other, false otherwise
     */
    bool operator>=(const GFNumber &other) const;

    /**
     * Overriding the <= operator
     * @param other object to compare with
     * @return true if the GFNumber is smaller than or equals to other, false otherwise
     */
    bool operator<=(const GFNumber &other) const;

    /**
     * Overriding the output of the GFNumber object.
     * @param out the stream
     * @param other the object to print
     * @return the stream
     */
    friend std::ostream &operator<<(std::ostream &out, const GFNumber &other);

    /**
     * Overriding the input of the GFNumber object.
     * @param out the stream
     * @param other the object to print
     * @return the stream
     */
    friend std::istream &operator>>(std::istream &in, GFNumber &other);
};

#endif //EX1_GFNUMBER_H
