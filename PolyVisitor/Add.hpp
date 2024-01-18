// File: PolyVisitor/Add.hpp

#ifndef Add_hpp
#define Add_hpp

#include "Rational.hpp"
#include "Polynomial.hpp"

// Adds the host Polynomial to the input parameter pRHS
// and returns the sum Polynomial.
class Add: public APolyAlgo {
public:
    virtual AObject* forConst(Polynomial* pLHS, AObject* pRHS);
    // Pre: pRHS is of type Polynomial*.

    virtual AObject* forNonConst(Polynomial* pLHS, AObject* pRHS);
    // Pre: pRHS is of type Polynomial*.
};

// Adds a constant to the host Polynomial.
class AddConst: public APolyAlgo {
private:
    Rational _coef;  // the constant to be added to the host Polynomial.

public:
    AddConst(const Rational &rat);
    // rat is the constant to be added to the host Polynomial.

    virtual AObject* forConst(Polynomial* pPoly, AObject* notUsed);
    virtual AObject* forNonConst(Polynomial* pPoly, AObject* notUsed);
};

// Adds a monomial to the host Polynomial.
class AddMono: public APolyAlgo {
    Rational _coef; // the coefficient and
    int _iOrder;    // the order of the monomial to be added 
    // to the host Polynomial.
public:
    AddMono(const Rational &coef, int iOrder);
    // coef is the coefficient of the monomial to be added to the host.
    // iOrder is the coefficient of the monomial to be added to the host.

    virtual AObject* forConst(Polynomial* pPoly, AObject* notUsed);
    virtual AObject* forNonConst(Polynomial* pPoly, AObject* notUsed);
};

#endif

