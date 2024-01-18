// File: PolyVisitor/WriteStream.hpp

#ifndef WriteStream_hpp
#define WriteStream_hpp

#include <iostream>  // ostream.
#include "Polynomial.hpp"
using namespace std;

// Writes the host Polynomial to an output stream, in the form:
// coefN  orderN
// coef  order
class WriteStream: public APolyAlgo {
private:
    ostream &_os;
public:
    WriteStream(ostream &os);
    virtual AObject* forConst(Polynomial* pPoly, AObject* );
    virtual AObject* forNonConst(Polynomial* pPoly, AObject* );
};

#endif
