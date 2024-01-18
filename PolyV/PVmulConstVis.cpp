/* 
 * File:   PVmulRatVis.cpp
 * Author: dxnguyen
 * 
 * Created on February 3, 2013, 9:25 PM
 */

#include "PolyCV.hpp"
#include "PVmulConstVis.hpp"

void PVmulConstVis::visitConstPolyV(AConstPolyV const &host) {
    _result = new ConstPolyCV(host.getLeadCoef() * _r);
}

void PVmulConstVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    if (_r == 0) {
        _result = new ConstPolyCV(0);
    } 
    else {
        host.getLowerPoly().accept(*this); // multiply the lower order poly by _r
        APolyV* mulLowerPoly = _result; // get the result
        _result = new NonConstPolyCV(host.getLeadCoef() * _r, host.getOrder(), *mulLowerPoly);
        delete mulLowerPoly; // collect garbage.
    }
}
