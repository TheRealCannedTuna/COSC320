/* 
 * File:   PVlongDivVis.hpp
 * Author: dxnguyen
 *
 * Created on May 12, 2013, 10:23 PM
 */

#ifndef PVLONGDIVVIS_HPP
#define PVLONGDIVVIS_HPP

#include "APolyVVis.hpp"

/**
 * Performs long division where the host is the divisor: the left hand side
 * is the divisor and the right hand side is the dividend.
 * The result consists of the quotient and the remainder.
 */
class PVlongDivVis : public APolyVVis {
private:
    APolyV const *_dividend;
    APolyV *_quotient;  // owned by this visitor
    APolyV *_remainder; // owned by this visitor

private:
    PVlongDivVis(const PVlongDivVis& orig); // disabled
    PVlongDivVis &operator=(PVlongDivVis const &rhs); // disabled

public:
    PVlongDivVis(APolyV const *dividend): _dividend(dividend) {
    }
    
    virtual ~PVlongDivVis() {
        delete _quotient;
        _quotient = nullptr;
        delete _remainder;
        _remainder = nullptr;
    }
    
    APolyV* getQuotient() {
        return _quotient->clone();  // the caller owns the requested quotient and is responsible for garbage collection
    }
    
    APolyV* getRemainder() {
        return _remainder->clone(); // the caller owns the requested remainder and is responsible for garbage collection
    }
    
    virtual void visitConstPolyV(AConstPolyV const &divisor);
    virtual void visitNonConstPolyV(ANonConstPolyV const &divisor);
};

#endif  /* PVLONGDIVVIS_HPP */

