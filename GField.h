//
// Created by Yair Shemer on 27/08/2019.
//

#ifndef EX1_GFIELD_H
#define EX1_GFIELD_H

#include <cmath>
#include <cassert>
#include <iostream>

class GFNumber;

/**
 * A class representing a galois field, containing a char and a degree, where the char is a prime
 * number.
 */
class GField
{
private:
    long _p; // char of the field
    long _l; //degree of the field
public:

    /**
     * A default constructor
     */
    GField();

    /**
     * A constructor obtaining only the char, where the degree is set to default 1
     * @param p char of the field
     */
    GField(long p);

    /**
     * A constructor obtaining both char and degree.
     * @param p char of the field
     * @param l degree of the field
     */
    GField(long p, long l);

    /**
     * A copy constructor.
     * @param other the galois field to copy
     */
    GField(const GField &other);

    /**
     * A destructor. Defined as default.
     */
    ~GField() = default;

    /**
     * Returns the char of the field.
     * @return the char of the field
     */
    long getChar() const;

    /**
     * Returns the degree of the field.
     * @return the degree of the field
     */
    long getDegree() const;

    /**
     * Returns the order of the field.
     * @return the order of the field
     */
    long getOrder() const;

    /**
     * A function to check if a number is a prime number.
     * @param p the number to check
     * @return true is prime, false otherwise
     */
    static bool isPrime(long p);

    /**
     * A function to calculate the greatest common divisor between a and b.
     * @param a first number
     * @param b second number
     * @return the gcd
     */
    GFNumber gcd(const GFNumber &a, const GFNumber &b);

    /**
     * A function to create a GFNumber with the given number.
     * @param k the number of the new GFNumber
     * @return the GFNumber
     */
    GFNumber createNumber(long k);

    /**
     * Overriding the copy assignment operator.
     * @param other the object to assign
     * @return the copy
     */
    GField &operator=(const GField &other) = default;

    /**
     * Overriding the == operator.
     * @param other the object to compare with
     * @return true upon equality, false otherwise
     */
    bool operator==(const GField &other) const;

    /**
     * Overriding the != operator.
     * @param other the object to compare with
     * @return true upon inequality, false otherwise
     */
    bool operator!=(const GField &other) const;

    /**
     * Overriding the output of the GField object.
     * @param out the stream
     * @param other the object to print
     * @return the stream
     */
    friend std::ostream &operator<<(std::ostream &out, const GField &other);

    /**
     *Overriding the input of the GField object.
     * @param in the stream
     * @param other the object to place the input
     * @return the stream
     */
    friend std::istream &operator>>(std::istream &in, GField &other);
};

#endif //EX1_GFIELD_H
