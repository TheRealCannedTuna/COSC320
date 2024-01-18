// File: PolyVisitor/ReadStream.hpp

#ifndef ReadStream_hpp
#define ReadStream_hpp

#include <iostream>  // istream.
#include "Polynomial.hpp"
using namespace std;

class ReadStream: public APolyAlgo {
    istream &_is;

public:
    ReadStream(istream &is);
    virtual AObject* forConst(Polynomial* pPoly, AObject* inp);
    virtual AObject* forNonConst(Polynomial* pPoly, AObject* inp);

private:
    void readStream(Polynomial* pPoly);
};

#endif
