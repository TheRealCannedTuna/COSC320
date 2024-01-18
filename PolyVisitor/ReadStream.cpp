// File: PolyVisitor/ReadStream.cpp

#include "ReadStream.hpp"

ReadStream::ReadStream(istream &is): _is(is) { }

AObject* ReadStream::forConst(Polynomial* pPoly, AObject* inp) {
    readStream(pPoly);
    return nullptr;
}

AObject* ReadStream::forNonConst(Polynomial* pPoly, AObject* inp) {
    readStream(pPoly);
    return nullptr;
}

void ReadStream::readStream(Polynomial* pPoly) {
    Rational coef = 0;  
    // read in a temp coef to make sure everything is OK first.
    if (_is >> coef) {
        int _iExp = 0;
        _is >> _iExp;
        if (0 != _iExp) {
            Polynomial lowerPoly;
            lowerPoly.execute(this, nullptr);
            *pPoly = Polynomial(coef, _iExp, lowerPoly);
        }
        else {
            *pPoly = Polynomial(coef);
        }
    }
}

