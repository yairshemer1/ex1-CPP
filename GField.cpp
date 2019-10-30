//
// Created by Yair Shemer on 27/08/2019.
//

#include "GField.h"
#include "GFNumber.h"
//-----------------------Constructors--------------------
/**
 * A default constructor
 */
GField::GField() : _p(2), _l(1)
{}

/**
 * A constructor obtaining only the char, where the degree is set to default 1
 * @param p char of the field
 */
GField::GField(long p) : _l(1)
{
    assert(isPrime(p));
    assert(p >= 0);
    _p = p;
}

/**
 * A constructor obtaining both char and degree.
 * @param p char of the field
 * @param l degree of the field
 */
GField::GField(long p, long l)
{
    assert(isPrime(p));
    assert(l > 0);
    _p = std::abs(p);
    _l = l;
}

/**
 * A copy constructor.
 * @param other the galois field to copy
 */
GField::GField(const GField &other) : _p(other.getChar()), _l(other.getDegree())
{}
//---------------------End Constructors-----------------

//--------------------------Getters---------------------
/**
 * Returns the char of the field.
 * @return the char of the field
 */
long GField::getChar() const
{
    return _p;
}

/**
 * Returns the degree of the field.
 * @return the degree of the field
 */
long GField::getDegree() const
{
    return _l;
}

/**
 * Returns the order of the field.
 * @return the order of the field
 */
long GField::getOrder() const
{
    return std::pow(_p, _l);
}
//---------------------End Getters--------------------
/**
 * A function to check if a number is a prime number.
 * @param p the number to check
 * @return true is prime, false otherwise
 */
bool GField::isPrime(long p)
{
    p = std::abs(p);
    if (p < 2)
    {
        return false;
    }
    for (int i = 2; i <= std::sqrt(p); i++)
    {
        if (p % i == 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * A function to calculate the greatest common divisor between a and b.
 * @param a first number
 * @param b second number
 * @return the gcd
 */
GFNumber GField::gcd(const GFNumber &a, const GFNumber &b)
{
    assert(a.getField() == b.getField());
    assert(a.getField() == *this);
    assert(a.getNumber() != 0 && b.getNumber() != 0);
    if ((a % b).getNumber() == 0)
    {
        return b;
    }
    return gcd(b, a % b);
}

/**
 * A function to create a GFNumber with the given number.
 * @param k the number of the new GFNumber
 * @return the GFNumber
 */
GFNumber GField::createNumber(long k)
{
    return GFNumber(k, *this);
}

/**
 * Overriding the == operator.
 * @param other the object to compare with
 * @return true upon equality, false otherwise
 */
bool GField::operator!=(const GField &other) const
{
    return (other.getOrder() != this->getOrder());
}

/**
 * Overriding the != operator.
 * @param other the object to compare with
 * @return true upon inequality, false otherwise
 */
bool GField::operator==(const GField &other) const
{
    return (other.getOrder() == this->getOrder());
}

/**
 * Overriding the output of the GField object.
 * @param out the stream
 * @param other the object to print
 * @return the stream
 */
std::ostream &operator<<(std::ostream &out, const GField &gf)
{
    out << "GF(" << gf.getChar() << "**" << gf.getDegree() << ")";
    return out;
}

/**
 *Overriding the input of the GField object.
 * @param in the stream
 * @param other the object to place the input
 * @return the stream
 */
std::istream &operator>>(std::istream &in, GField &gf)
{
    long p, l;
    in >> p >> l;
    assert(!in.fail());
    gf = GField(p, l);
    return in;
}