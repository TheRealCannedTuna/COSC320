/* 
 * File:   PVmulMonoVis.cpp
 * Author: dxnguyen
 * 
 * Created on May 16, 2013, 10:21 PM
 */

#include "PVmulMonoVis.hpp"
#include "PolyCV.hpp"

void PVmulMonoVis::visitConstPolyV(AConstPolyV const &host) {
    if (host.getLeadCoef() == 0) {
        _result = new ConstPolyCV();  // the zero polynomial
    }
    else {
        _result = new NonConstPolyCV(host.getLeadCoef() * _coef, _order);
    }
}

void PVmulMonoVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    host.getLowerPoly().accept(*this); // multiply the monomial with the lower order poly.
    APolyV *lowerProd = _result; // get the result.
    _result = new NonConstPolyCV(host.getLeadCoef() * _coef, host.getOrder() + _order, *lowerProd);
    delete lowerProd; // collect garbage.
}

