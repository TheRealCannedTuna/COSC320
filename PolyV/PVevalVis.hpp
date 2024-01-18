/* 
 * File:   PVevalVis.hpp
 * Author: dxnguyen
 *
 * Created on January 27, 2013, 11:48 PM
 */

#ifndef PVEVALVIS_HPP
#define PVEVALVIS_HPP

#include "APolyVVis.hpp"

class PVevalVis : public APolyVVis {
private:
    Rational _r;
    Rational _result;

    PVevalVis(const PVevalVis& orig);
public:

    PVevalVis(Rational const & r) : _r(r) {
    }
    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);

    Rational &result() {
        return _result;
    }
};

#endif  /* PVEVALVIS_HPP */

