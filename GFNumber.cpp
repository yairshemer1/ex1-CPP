//
// Created by Yair Shemer on 27/08/2019.
//
#include "GFNumber.h"
#include <random>

//---------------------Constructors------------------------
/**
 * Default constructor. Initializes the field values as it's default, and the number to 0.
 */
GFNumber::GFNumber() : _n(0)
{}

/**
 * A constructor that initializes the field as it's default and the number to the given n.
 * @param n the number
 */
GFNumber::GFNumber(long n)
{
    _n = _calcModulo(n);
}

/**
 * A constructor given both field value and n value.
 * @param n the number
 * @param gf the field
 */
GFNumber::GFNumber(long n, const GField &gf) : _gf(gf)
{
    _n = _calcModulo(n);
}

/**
 * A copy constructor
 * @param other the GFNumber to copy
 */
GFNumber::GFNumber(const GFNumber &other) : _gf(other.getField()), _n(other.getNumber())
{}
//-------------------End Constructors-----------------
//----------------------Getters------------------------
/**
 * Returns the number of the GFNumber
 * @return the number
 */
long GFNumber::getNumber() const
{
    return _n;
}

/**
 * Returns the field of the GFNumber
 * @return the field
 */
GField GFNumber::getField() const
{
    return _gf;
}
//---------------------- End Getters---------------------
/**
 * A function to calculate a list of all prime factors creating the GFNumber
 * @param counter counts the amount of factors
 * @return the list of prime factors
 */
GFNumber *GFNumber::getPrimeFactors(int *counter)
{
    *counter = 0;
    GFNumber *factorsList = nullptr;
    GFNumber GFN2 = _gf.createNumber(2);
    GFNumber GFN0 = _gf.createNumber(0);
    GFNumber current = *this;
    if (current.getNumber() == 0 || current.getIsPrime() || current.getNumber() == 1)
    {
        return factorsList;
    }
    while (current % GFN2 == GFN0)
    {
        current /= GFN2;
        factorsList = GFNumber::_expandArray(factorsList, *counter, GFN2);
    }
    if (current.getNumber() == 1)
    {
        return factorsList;
    }
    if (current.getIsPrime())
    {
        factorsList = GFNumber::_expandArray(factorsList, *counter, current);
        return factorsList;
    }
    //by now current holds an odd number, time to use rho's algorithm...
    GFNumber p = current._pollardRho();
    while (p != GFN0)
    {
        current /= p;
        if(!p.getIsPrime())
        {
            factorsList = p._bruteForce(factorsList, *counter);
        }
        else
        {
            factorsList = GFNumber::_expandArray(factorsList, *counter, p);
        }
        if (current.getIsPrime())
        {
            break;
        }
        p = current._pollardRho();
    }
    //rho is no more effective by now, find numbers by brute force
    if (current.getIsPrime())
    {
        factorsList = GFNumber::_expandArray(factorsList, *counter, current);
    }
    else
    {
        factorsList = current._bruteForce(factorsList, *counter);
    }
    return factorsList;
}

/**
 * A function to print the list returned from getPrimeFactors. It will allocate memory and
 * free it itself.
 */
void GFNumber::printFactors()
{
    int counter = 0;
    GFNumber *factorsList = getPrimeFactors(&counter);
    std::cout << this->getNumber() << "=";
    if (counter == 0)
    {
        std::cout << this->getNumber() << "*1" << std::endl;
        return;
    }
    for (int i = 0; i < counter - 1; i++)
    {
        std::cout << factorsList[i].getNumber() << "*";
    }
    std::cout << factorsList[counter - 1].getNumber() << std::endl;
    delete[] factorsList;
}

/**
 * A function to check if the GFNumber is a prime number
 * @return true for prime, false otherwise
 */
bool GFNumber::getIsPrime()
{
    return GField::isPrime(this->getNumber());
}

/**
 * A function to create a number in the field from a given number
 * @param n the given number
 * @return the number in the field
 */
long GFNumber::_calcModulo(long n)
{
    n = n % this->getField().getOrder();
    if (n < 0)
    {
        n += this->getField().getOrder();
    }
    return n;
}

/**
 * A function to manage the list memory allocations, including deleting and returning a
 * bigger array
 * @param arr the older array
 * @param counter reference to control on how many objects in the array at the moment
 * @param last the GFNumber to enter the last cell of the array
 * @return the bigger array
 */
GFNumber *GFNumber::_expandArray(GFNumber *arr, int &counter, const GFNumber &last)
{
    GFNumber *newArray;
    if (counter == 0)
    {
        counter = 1;
    }
    else
    {
        counter++;
    }
    newArray = new GFNumber[counter];
    for (int i = 0; i < counter - 1; i++)
    {
        newArray[i] = arr[i];
    }
    newArray[counter - 1] = last;
    delete[] arr;
    return newArray;
}

/**
 * A function x^2 +1
 * @param x a GFNumber
 * @param mod the modulo
 * @return the result
 */
GFNumber GFNumber::_f(const GFNumber &x, const long mod)
{
    return x.getField().createNumber((x.getNumber() * x.getNumber() + 1) % mod);
}

/**
 * An algorithm that is supposed to calculate factors of a given number
 * @return a GFNumber that divides the current number
 */
GFNumber GFNumber::_pollardRho()
{
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> random(1, _n - 1);
    GFNumber x = _gf.createNumber(random(gen));
    GFNumber y(x);
    GFNumber p = _gf.createNumber(1);
    long mod = _n;
    while (p.getNumber() == 1)
    {
        x = _f(x, mod);
        y = _f(_f(y, mod), mod);
        if (x > y)
        {
            p = _gf.gcd(x - y, *this);
        }
        else
        {
            p = _gf.gcd(y - x, *this);
        }
    }
    if (p == *this)
    {
        return _gf.createNumber(0);
    }
    return p;
}

/**
 * A function to add a given list the current GFNumber.
 * @param currentList the list before adding to is the current GFNumber
 * @param counter reference to a counter, the size of the array
 * @return A list of GFNumber including current number and older list
 */
GFNumber *GFNumber::_bruteForce(GFNumber *currentList, int &counter)
{
    GFNumber GFN0 = _gf.createNumber(0);
    long i = 2, bound = std::sqrt(this->getNumber());
    while (i <= bound)
    {
        GFNumber div = _gf.createNumber(i);
        if (*this % div == GFN0)
        {
            *this /= div;
            currentList = GFNumber::_expandArray(currentList, counter, div);
        }
        else
        {
            i++;
        }
    }
    return currentList;
}

/**
 * Overriding the == operator
 * @param other the object to compare with
 * @return true for equality, false otherwise
 */
bool GFNumber::operator==(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return (this->getField().getOrder() == other.getField().getOrder() &&
            this->getNumber() == other.getNumber());
}

/**
 * Overriding the != operator
 * @param other the object to compare with
 * @return true for inequality, false otherwise
 */
bool GFNumber::operator!=(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return (this->getField().getOrder() != other.getField().getOrder() ||
            this->getNumber() != other.getNumber());
}

/**
 * Overriding the + operator
 * @param other object as a GFNumber
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator+(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return GFNumber(this->getNumber() + other.getNumber(), other.getField());
}

/**
 * Overriding the + operator
 * @param other object as a long
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator+(const long &other) const
{
    return GFNumber(this->getNumber() + other, this->getField());
}

/**
 * Overriding the += operator
 * @param other object as a GFNumber
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber &GFNumber::operator+=(const GFNumber &other)
{
    assert(this->getField() == other.getField());
    this->_n = _calcModulo(this->getNumber() + other.getNumber());
    return *this;
}

/**
 * Overriding the += operator
 * @param other object as a long
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber &GFNumber::operator+=(const long &other)
{
    this->_n += other;
    this->_n = _calcModulo(this->_n);
    return *this;
}

/**
 * Overriding the - operator
 * @param other object as a GFNumber
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator-(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return GFNumber(this->getNumber() - other.getNumber(), other.getField());
}

/**
 * Overriding the - operator
 * @param other object as a long
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator-(const long &other) const
{
    return GFNumber(this->getNumber() - other, this->getField());
}

/**
 * Overriding the -= operator
 * @param other object as a GFNumber
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator-=(const GFNumber &other)
{
    assert(this->getField() == other.getField());
    this->_n = _calcModulo(this->getNumber() - other.getNumber());
    return *this;
}

/**
 * Overriding the -= operator
 * @param other object as a long
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber &GFNumber::operator-=(const long &other)
{
    this->_n -= other;
    this->_n = _calcModulo(this->_n);
    return *this;
}

/**
 * Overriding the * operator
 * @param other object as a GFNumber
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator*(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return GFNumber(this->getNumber() * other.getNumber(), other.getField());

}

/**
 * Overriding the * operator
 * @param other object as a long
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator*(const long &other) const
{
    return GFNumber(this->getNumber() * other, this->getField());
}

/**
 * Overriding the *= operator
 * @param other object as a GFNumber
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator*=(const GFNumber &other)
{
    assert(this->getField() == other.getField());
    this->_n = _calcModulo(this->getNumber() * other.getNumber());
    return *this;
}

/**
 * Overriding the *= operator
 * @param other object as a long
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber &GFNumber::operator*=(const long &other)
{
    this->_n *= other;
    this->_n = _calcModulo(this->_n);
    return *this;
}

/**
 * Overriding the / operator
 * @param other object as a GFNumber
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator/(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return GFNumber(this->getNumber() / other.getNumber(), other.getField());
}

/**
 * Overriding the /= operator
 * @param other object as a GFNumber
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber &GFNumber::operator/=(const GFNumber &other)
{
    assert(this->getField() == other.getField());
    this->_n = _calcModulo(this->getNumber() / other.getNumber());
    return *this;
}

/**
 * Overriding the % operator
 * @param other object as a GFNumber
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator%(const GFNumber &other) const
{
    assert(this->getField() == other.getField());
    return GFNumber(this->getNumber() % other.getNumber(), other.getField());

}

/**
 * Overriding the % operator
 * @param other object as a long
 * @return A new GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator%(const long &other) const
{
    assert(other != 0);
    return GFNumber(this->getNumber() % other, this->getField());
}

/**
 * Overriding the %= operator
 * @param other object as a GFNumber
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber GFNumber::operator%=(const GFNumber &other)
{
    assert(this->getField() == other.getField());
    this->_n = this->getNumber() % other.getNumber();
    return *this;
}

/**
 * Overriding the %= operator
 * @param other object as a long
 * @return A reference to the same GFNumber with the correct arithmetic action
 */
GFNumber &GFNumber::operator%=(const long &other)
{
    this->_n %= _calcModulo(other);
    this->_n = _calcModulo(this->_n);
    return *this;
}

/**
 * Overriding the > operator
 * @param other object to compare with
 * @return true if the GFNumber is bigger than other, false otherwise
 */
bool GFNumber::operator>(const GFNumber &other) const
{
    return this->getNumber() > other.getNumber();
}

/**
 * Overriding the < operator
 * @param other object to compare with
 * @return true if the GFNumber is smaller than other, false otherwise
 */
bool GFNumber::operator<(const GFNumber &other) const
{
    return this->getNumber() < other.getNumber();
}

/**
 * Overriding the >= operator
 * @param other object to compare with
 * @return true if the GFNumber is bigger than or equals to other, false otherwise
 */
bool GFNumber::operator>=(const GFNumber &other) const
{
    return this->getNumber() >= other.getNumber();
}

/**
 * Overriding the <= operator
 * @param other object to compare with
 * @return true if the GFNumber is smaller than or equals to other, false otherwise
 */
bool GFNumber::operator<=(const GFNumber &other) const
{
    return this->getNumber() <= other.getNumber();
}

/**
 * Overriding the output of the GFNumber object.
 * @param out the stream
 * @param other the object to print
 * @return the stream
 */
std::ostream &operator<<(std::ostream &out, const GFNumber &other)
{
    out << other.getNumber() << " " << other.getField();
    return out;
}

/**
 * Overriding the input of the GFNumber object.
 * @param out the stream
 * @param other the object to print
 * @return the stream
 */
std::istream &operator>>(std::istream &in, GFNumber &other)
{
    GField inField;
    long n;
    in >> n >> inField;
    assert(!in.fail());
    other = GFNumber(n, inField);
    return in;
}
