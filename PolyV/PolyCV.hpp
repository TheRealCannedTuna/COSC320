/* 
 * File:   PolyC.hpp
 * Author: dxnguyen
 *
 * Created on January 17, 2013, 11:41 PM
 */

#ifndef POLYCV_HPP
#define POLYCV_HPP

#include <assert.h>
#include "APolyV.hpp"

class ConstPolyCV : public AConstPolyV {
private:
    Rational _coef;

private:
    ConstPolyCV &operator=(const ConstPolyCV &rhs); //not implemented to disallow usage.
    ConstPolyCV(const ConstPolyCV& orig);

public:

    ConstPolyCV(Rational const &coef = 0) : _coef(coef) {
    }

    virtual ~ConstPolyCV() {
    }

    virtual Rational getLeadCoef() const {
        return _coef;
    }

    virtual APolyV *clone() const {
        return new ConstPolyCV(_coef);
    }

};

class NonConstPolyCV : public ANonConstPolyV {
private:
    Rational _coef;
    int _order;
    APolyV *_lowerPoly; // need pointer for polymorphic behavior.

private:
    NonConstPolyCV &operator=(const NonConstPolyCV &rhs); //not implemented to disallow usage.
    NonConstPolyCV(const NonConstPolyCV& orig);

public:

    NonConstPolyCV(Rational const &coef, int order, APolyV const &lowerPoly) :
        _coef(coef), _order(order), _lowerPoly(lowerPoly.clone()) {
        assert(coef != 0 );
        assert(order > lowerPoly.getOrder());
    }

    // Creates a monomial with order > 0
    NonConstPolyCV(Rational const &coef, int order) :
        _coef(coef), _order(order), _lowerPoly(new ConstPolyCV()) {
        assert(coef != 0);
        assert(order > 0);
    }

    virtual ~NonConstPolyCV() {

        delete _lowerPoly;
    }

    virtual Rational getLeadCoef() const {

        return _coef;
    }

    virtual int getOrder() const {

        return _order;
    }

    virtual APolyV const &getLowerPoly() const {

        return *_lowerPoly;
    }

    virtual APolyV *clone() const {
        return new NonConstPolyCV(_coef, _order, *_lowerPoly);
    }
};

#endif

