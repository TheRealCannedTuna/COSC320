/* 
 * File:   PVmulVis.cpp
 * Author: dxnguyen
 * 
 * Created on March 12, 2013, 11:56 AM
 */

#include "PVmulVis.hpp"
#include "PolyCV.hpp"
#include "PVmulMonoVis.hpp"

void PVmulVis::visitConstPolyV(AConstPolyV const &host) {
    _result = host.getLeadCoef() * (*_rhs);
}

void PVmulVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    host.getLowerPoly().accept(*this);
    APolyV *lowerProd = _result;
    PVmulMonoVis mmv(host.getLeadCoef(), host.getOrder());
    _rhs->accept(mmv);
    APolyV* leadProd = mmv.result();
    _result = (*leadProd) + (*lowerProd);
    delete lowerProd;
    delete leadProd;
}
