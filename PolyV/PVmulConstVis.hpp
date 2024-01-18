/* 
 * File:   PVmulConstVis.hpp
 * Author: dxnguyen
 *
 * Created on February 3, 2013, 9:25 PM
 */

#ifndef PVMULCONSTVIS_HPP
#define PVMULCONSTVIS_HPP

#include "APolyVVis.hpp"

class PVmulConstVis : public APolyVVis {
private:
    Rational _r;
    APolyV* _result;  // owned by this visitor.

private:
    PVmulConstVis(const PVmulConstVis& orig);


public:

    PVmulConstVis(Rational const &r) : _r(r) {
    }

    virtual ~PVmulConstVis() {
        delete _result;
        _result = nullptr;
    }
    
    APolyV* result() {
        return _result->clone();  // the caller owns the requested result and is responsible for garbage collection.
    }
    
    void setMultiplier(Rational const &r) {
        _r = r;
    }
    
    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);
};

#endif

