// File: Rational/Rational.cpp

#include "Rational.hpp"
#include "Utilities.hpp" // abs, sgn, gcd.

Rational::Rational(int numerator, int denominator) {
    if (0 == denominator) {
        cerr << "Rational precondition violated: 0 == denominator" << endl;
        throw -1;
    }
    _numerator = abs(numerator);
    _denominator = abs(denominator);
    int gcdTemp = gcd(_numerator, _denominator);
    _numerator = sgn(numerator) * sgn(denominator) * _numerator / gcdTemp;
    _denominator = _denominator / gcdTemp;
}

Rational::Rational(Rational const &rhs) {
    _numerator = rhs._numerator;
    _denominator = rhs._denominator;
}

double Rational::toDouble() const {
    return static_cast<double> (_numerator) / static_cast<double> (_denominator);
}

int Rational::numerator() const {
    return _numerator;
}

int Rational::denominator() const {
    return _denominator;
}

Rational operator+(Rational const &lhs, Rational const &rhs) {
    int gcdTemp = gcd(lhs.denominator(), rhs.denominator());
    int lhsMul = rhs.denominator() / gcdTemp;
    int rhsMul = lhs.denominator() / gcdTemp;
    return Rational(lhs.numerator() * lhsMul + rhs.numerator() * rhsMul, lhs.denominator() * lhsMul);
}

Rational operator-(Rational const &lhs, Rational const &rhs) {
    cerr << "operator- (binary): Exercise for the student." << endl;
    throw -1;
}

Rational operator*(Rational const &lhs, Rational const &rhs) {
    cerr << "operator*: Exercise for the student." << endl;
    throw -1;
}

Rational operator/(Rational const &lhs, Rational const &rhs) {
    cerr << "operator/: Exercise for the student." << endl;
    throw -1;
}

Rational operator-(Rational const &rhs) {
    cerr << "operator- (unary): Exercise for the student." << endl;
    throw -1;
}

bool operator==(Rational const &lhs, Rational const &rhs) {
    cerr << "operator==: Exercise for the student." << endl;
    throw -1;
}

bool operator!=(Rational const &lhs, Rational const &rhs) {
    return !(lhs == rhs);
}

bool operator<(Rational const &lhs, Rational const &rhs) {
    cerr << "operator<: Exercise for the student." << endl;
    throw -1;
}

bool operator>(Rational const &lhs, Rational const &rhs) {
    return !(lhs == rhs) && !(lhs < rhs);
}

ostream &operator<<(ostream &os, Rational const &rhs) {
    cerr << "operator<<: Exercise for the student." << endl;
    throw -1;
}

istream &operator>>(istream &is, Rational &rhs) {
    int numerator, denominator = 1;
    is >> numerator;
    char c = (char) is.peek();
    if (c == '/') {
        is >> c >> denominator;
    }
    rhs = Rational(numerator, denominator);
    return is;
}
