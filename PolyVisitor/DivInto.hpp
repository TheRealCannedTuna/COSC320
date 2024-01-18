// File: PolyVisitor/DivInto.hpp

#ifndef DivInto_hpp
#define DivInto_hpp

#include "Polynomial.hpp"

// The host polynomial is the divisor, and the input parameter
// is the dividend.
class DivInto: public APolyAlgo {
public:
    virtual AObject* forConst(Polynomial* pDivisor, AObject* pDividend);
    virtual AObject* forNonConst(Polynomial* pDivisor, AObject* pDividend);
};

#endif
