/* 
 * File:   PVaddVis.cpp
 * Author: dxnguyen
 * 
 * Created on February 2, 2013, 10:18 PM
 */

#include "PVaddVis.hpp"
#include "PolyCV.hpp"

// Add a constant to the host polynomial, an intermediate computation
// in polynomial addition.

class PVaddConstVis : public APolyVVis {
private:
    Rational _r;
    APolyV *_result;

public:

    PVaddConstVis(Rational const &r) : _r(r) {
    }
    
    virtual ~PVaddConstVis() {
        _result = nullptr;
    }
    
    void visitConstPolyV(AConstPolyV const &host);
    void visitNonConstPolyV(ANonConstPolyV const &host);

    APolyV *result() {
        return _result;
    }
};

// Add a monomial to the host polynomial, an intermediate computation
// in polynomial addition.

class PVaddMonoVis : public APolyVVis {
private:
    Rational _coef; // pre: _coef != 0
    int _order;  // pre: _order > 0
    APolyV *_result;

public:

    PVaddMonoVis(Rational const &coef, int order) : _coef(coef), _order(order) {
    }
    
    virtual ~PVaddMonoVis() {
        _result = nullptr;
    }
    
    void visitConstPolyV(AConstPolyV const &host);
    void visitNonConstPolyV(ANonConstPolyV const &host);

    APolyV *result() {
        return _result;
    }
};

void PVaddVis::visitConstPolyV(AConstPolyV const &host) {
    PVaddConstVis addConstVis(host.getLeadCoef());
    _rhs->accept(addConstVis);
    _result = addConstVis.result();
}

void PVaddVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    host.getLowerPoly().accept(*this);
    APolyV* lowerSum = _result;
    PVaddMonoVis addMonoVis(host.getLeadCoef(), host.getOrder());
    lowerSum->accept(addMonoVis);
    _result = addMonoVis.result();
    delete lowerSum;
}

void PVaddConstVis::visitConstPolyV(AConstPolyV const &host) {
    _result = new ConstPolyCV(host.getLeadCoef() + _r);
}

void PVaddConstVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    host.getLowerPoly().accept(*this); // add the constant to the lower order poly.
    APolyV *lowerSum = _result; // get the result.
    _result = new NonConstPolyCV(host.getLeadCoef(), host.getOrder(), *lowerSum);
    delete lowerSum; // collect garbage.
}

void PVaddMonoVis::visitConstPolyV(AConstPolyV const &host) {
    _result = new NonConstPolyCV(_coef, _order, host);
}

void PVaddMonoVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    if (host.getOrder() < _order) {
        _result = new NonConstPolyCV(_coef, _order, host);
    }
    else if (host.getOrder() == _order) {
        Rational coefSum = _coef + host.getLeadCoef();
        if (coefSum == 0) {
            _result = host.getLowerPoly().clone();
        }
        else {
            _result = new NonConstPolyCV(coefSum, _order, host.getLowerPoly());
        }
    }
    else { // host.getOrder() > _order 
        host.getLowerPoly().accept(*this); // add the monomial to the lower order polynomial
        APolyV *lowerSum = _result;  // get the result
        _result = new NonConstPolyCV(host.getLeadCoef(), host.getOrder(), *lowerSum);
        delete lowerSum;  // clean up
    }      
}
