// File: PolyVisitor/WriteStream.cpp

#include "WriteStream.hpp"

WriteStream::WriteStream(ostream &os): _os(os) { }

AObject* WriteStream::forConst(Polynomial* pPoly, AObject* ) {
    _os << pPoly->getLeadCoef() << '\t' << 0 << endl;
    return nullptr;
}

AObject* WriteStream::forNonConst(Polynomial* pPoly, AObject* ) {
    _os << pPoly->getLeadCoef() << '\t' << pPoly->iGetOrder() << endl;
    pPoly->getLowerPoly().execute(this, nullptr);
    return nullptr;
}

