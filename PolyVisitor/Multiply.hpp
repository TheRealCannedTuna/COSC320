// File: PolyVisitor/Multiply.hpp

#ifndef Multiply_hpp
#define Multiply_hpp

#include "Polynomial.hpp"

class Multiply: public APolyAlgo {
public:
    virtual AObject* forConst(Polynomial* pLHS, AObject* pRHS);
    virtual AObject* forNonConst(Polynomial* pLHS, AObject* pRHS);
};

#endif
