/* 
 * File:   PVmulMonoVis.hpp
 * Author: dxnguyen
 *
 * Created on May 16, 2013, 10:21 PM
 */

#ifndef PVMULMONOVIS_HPP
#define PVMULMONOVIS_HPP

#include <assert.h>
#include "APolyVVis.hpp"

// Multiply a monomial with the host polynomial.
class PVmulMonoVis : public APolyVVis {
private:
    Rational _coef; // pre: _coef != 0
    int _order;     // pre: _order > 0
    APolyV *_result; // owned by this visitor.

public:

    PVmulMonoVis(Rational const &coef, int order) : _coef(coef), _order(order) {
        assert(coef != 0 );
        assert(order > 0);
    }

    virtual ~PVmulMonoVis() {
        delete _result;
        _result = nullptr;
    }

    void visitConstPolyV(AConstPolyV const &host);
    void visitNonConstPolyV(ANonConstPolyV const &host);

    APolyV *result() {
        return _result->clone(); // the caller owns the requested result and is responsible for garbage collection.
    }
};

#endif  /* PVMULMONOVIS_HPP */

