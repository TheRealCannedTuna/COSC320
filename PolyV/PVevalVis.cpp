/* 
 * File:   PVevalVis.cpp
 * Author: dxnguyen
 * 
 * Created on January 27, 2013, 11:48 PM
 */

#include "PVevalVis.hpp"

class PVevalHelpVis : public APolyVVis {
    // implements Horner's algorithm for evaluating polynomials.
private:
    Rational _r;
    Rational _acc;
    Rational _result;
public:

    PVevalHelpVis(Rational const & r, Rational const & acc) : _r(r), _acc(acc) {
    }
    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);
    Rational &result() {
        return _result;
    }
};

void PVevalVis::visitConstPolyV(AConstPolyV const &host) {
    _result = host.getLeadCoef();
}

void PVevalVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    PVevalHelpVis evalHelpVis(_r, 0);
    host.accept(evalHelpVis);
    _result = evalHelpVis.result();
}

void PVevalHelpVis::visitConstPolyV(AConstPolyV const &host) {
    _result = _acc + host.getLeadCoef();
}

void PVevalHelpVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    _acc = _acc + host.getLeadCoef();
    int order = host.getOrder();
    for (int i = host.getLowerPoly().getOrder(); i < order; i++) {
        _acc = _acc * _r;
    }
    host.getLowerPoly().accept(*this);
}

