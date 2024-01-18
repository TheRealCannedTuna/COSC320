// File: PolyVisitor/Polynomial.hpp

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <iostream>  // istream, ostream.
#include "AObject.hpp"
#include "Rational.hpp"
using namespace std;

class APolyNode;
class APolyAlgo;

// Represents single variable polynomials with rational coefficients.
// Uses the Visitor pattern where Polynomial is the host and the algorithms
// on Polynomial are visitors.
class Polynomial: public virtual AObject {
    friend class ConstNode;
    friend class NonConstNode;

private:
    APolyNode* _headNode;

public:
    Polynomial(const Rational &coef = 0, int order = 0);
    //Pre :  order >= 0.
    //Post:  if coef == 0 or order = 0 initialized to a constant polynomial 
    //       else initialized to monomial of degree = order.

    Polynomial(const Rational &coef, int order, const Polynomial &lowerOrderTerms);
    //Pre: degree of lowerOrderTerms < order.
    //Post:  if coef == 0 then initialized to the lowerOrderTerms polynomial 
    //       else initialized to a polynomial of degree = order with coefficient coef
    //        and the lower order polynomial equal to lowerOrderTerms.

    Polynomial(const Polynomial &poly);

    ~Polynomial();

    Polynomial &operator =(const Polynomial &rhs);

    int iGetOrder() const;
    Rational getLeadCoef() const;
    Polynomial getLowerPoly() const;
    AObject* execute(APolyAlgo* pAlgo, AObject* inp); 
    // Hook to Polynomial framework: Don't call me!  I'll call you.
};

/**
   Visitor to Polynomial.
   Represents an algorithm on Polynomial.
*/
class APolyAlgo: public virtual AObject {
    APolyAlgo &operator =(const APolyAlgo &rhs); //not implemented to disallow usage.
public:
    virtual AObject* forConst(Polynomial* pPoly, AObject* inp)= 0;
    virtual AObject* forNonConst(Polynomial* pPoly, AObject* inp)= 0;
};

// Standard C++ overloaded I/O operators.
// Illustrate use of ReadStream and WriteStream visitors.
ostream &operator <<(ostream &os, const Polynomial &poly);
istream &operator >>(istream &os, Polynomial &poly);

// Illustrates use of Add visitor.
Polynomial operator +(const Polynomial &lhs, const Polynomial &rhs);

#endif
