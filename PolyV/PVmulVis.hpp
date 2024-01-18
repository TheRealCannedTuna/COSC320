/* 
 * File:   PVmulVis.hpp
 * Author: dxnguyen
 *
 * Created on March 12, 2013, 11:56 AM
 */

#ifndef PVMULVIS_HPP
#define PVMULVIS_HPP

#include "APolyVVis.hpp"

class PVmulVis: public APolyVVis {
private:
    APolyV const *_rhs;
    APolyV *_result;  // owned by this visitor

private:
    PVmulVis(const PVmulVis& orig);  // disabled
    PVmulVis &operator=(PVmulVis const &rhs); // disabled

public:
    PVmulVis(APolyV const *rhs) : _rhs(rhs) {
    }
    
    virtual ~PVmulVis() {
        delete _result;
        _result = nullptr;
    }

    APolyV* result() {
        return _result->clone();  // the caller owns the requested result and is responsible for garbage collection.
    }

    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);
};

#endif  /* PVMULVIS_HPP */

