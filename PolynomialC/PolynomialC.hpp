// File: Polynomial/PolynomialC.hpp

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <iostream>  // istream, ostream.
#include "Rational.hpp"
using namespace std;

class APolyNode;  // forward declaration

class PolynomialC {
    friend class ConstNode;
    friend class NonConstNode;

    friend ostream &operator <<(ostream &os, PolynomialC const &poly);
    //example:  3/2 x**4 - 5 x**2 + 1 will output as
    // 3/2 4
    // -5  2
    // 1   0

    friend istream &operator >>(istream &os, PolynomialC &poly);
    // basically the inverse of <<.

    friend PolynomialC operator +(PolynomialC const &lhs, PolynomialC const &rhs);
    // make operator+ a global function to allow implicit type conversion such as
    // 3 + aPolynomial.

private:
    APolyNode* _headNode;

public:
    PolynomialC(Rational const &coef = 0, int order = 0);
    //Pre :  order >= 0.
    //Post:  if coef == 0 or order = 0 initialized to a constant polynomial
    //       else initialized to monomial of degree = order with coefficient coef.

    PolynomialC(Rational const &coef, int order, PolynomialC const &lowerOrderPoly);
    //Pre: degree of lowerOrderPoly < order.
    //Post:  if coef == 0 then initialized to the lowerOrderPoly polynomial
    //       else initialized to a polynomial of degree = order with coefficient coef
    //         and the lower order polynomial equal to lowerOrderPoly.

    PolynomialC(PolynomialC const &poly);

    ~PolynomialC();

    PolynomialC &operator =(PolynomialC const &rhs);

    int getOrder() const;
    Rational getLeadCoef() const;
    PolynomialC getLowerPoly() const;

    Rational operator()(Rational const &r) const;
    // Overload the function call operator to evaluate the target polynomial
    // at the given Rational r.
};

#endif
