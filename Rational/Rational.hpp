// File: Rational/Rational.hpp

#ifndef Rational_hpp
#define Rational_hpp

#include <iostream> // istream, ostream.
using namespace std;

class Rational {
private:
    int _numerator;
    int _denominator;
    // Invariant: 0 < _denominator.
    // Invariant: gcd(_numerator, _denominator) == 1.

public:
    Rational(int numerator = 0, int denominator = 1);
    // Post: This Rational is numerator/denominator.

    Rational(Rational const &rhs);
    // Post: This Rational is a copy of rhs.

    double toDouble() const;
    // Post: The double value of this Rational is returned.

    int numerator() const;
    int denominator() const;
};

// Overloaded binary algebraic operators.
Rational operator+(Rational const &lhs, Rational const &rhs);
Rational operator-(Rational const &lhs, Rational const &rhs);
Rational operator*(Rational const &lhs, Rational const &rhs);
Rational operator/(Rational const &lhs, Rational const &rhs);
// Pre: rhs != 0.

// Overloaded unary negation operator.
Rational operator-(Rational const &rhs);

// Overloaded comparison operators.
bool operator==(Rational const &lhs, Rational const &rhs);
bool operator!=(Rational const &lhs, Rational const &rhs);
bool operator<(Rational const &lhs, Rational const &rhs);
bool operator>(Rational const &lhs, Rational const &rhs);

// Overloaded input and output operators.
ostream &operator<<(ostream &os, Rational const &rhs);
istream &operator>>(istream &is, Rational &rhs);
// Pre: The next input in is has the form a or a/b, where a, b are int.

#endif

