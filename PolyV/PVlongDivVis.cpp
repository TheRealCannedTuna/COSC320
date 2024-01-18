/* 
 * File:   PVlongDivVis.cpp
 * Author: dxnguyen
 * 
 * Created on May 12, 2013, 10:23 PM
 */

#include "PVlongDivVis.hpp"
#include "PolyCV.hpp"
#include "PVmulMonoVis.hpp"

/**
 * Pre: the divisor is not the zero polynomial.
 * The quotient is the dividend divided by the divisor's coefficient.
 * The remainder is the zero polynomial.
 */
void PVlongDivVis::visitConstPolyV(AConstPolyV const &divisor) {
    Rational coef = divisor.getLeadCoef();
    if (coef == 0) {
        cerr << "Division by 0!" << endl;
        throw -1;
    }
    _quotient = (1 / coef) * (*_dividend);
    _remainder = new ConstPolyCV(); // the zero polynomial
}

/**
 * Performs different computations for three different cases:
 * dividend's order < divisor's order
 * dividend's order == divisor's order
 * dividend's order > divisor's order
 */
void PVlongDivVis::visitNonConstPolyV(ANonConstPolyV const &divisor) {
    int dividendOrder = _dividend->getOrder();
    int divisorOrder = divisor.getOrder();
    if (dividendOrder < divisorOrder) {
        // the quotient is zero and the remainder is the dividend
        _quotient = new ConstPolyCV();  // the zero polynomial
        _remainder = _dividend->clone();
    }
    // At this point, the dividend's order >= the divisor's order > 0;
    // thus the dividend must be a non-constant polynomial.  This justifies
    // the use of static cast to type-cast the dividend to a non-constant polynomial.
    else if (dividendOrder == divisorOrder) {
        // The quotient is the constant polynomial (dividend's lead coef)/(divisor's lead coef).
        // The remainder is the difference between the rest of the
        // dividend and the product of the quotient and the rest of the divisor.
        Rational quotCoef = _dividend->getLeadCoef() / divisor.getLeadCoef();
        _quotient = new ConstPolyCV(quotCoef);
        _remainder = (static_cast<const ANonConstPolyV*>(_dividend))->getLowerPoly() 
            - *(quotCoef * divisor.getLowerPoly());
    }
    else { // dividendOrder > divisorOrder)
        // The quotient must be a non-constant polynomial whose order is:
        int quotOrder = dividendOrder - divisorOrder;  // > 0
        // with leading coefficient:
        Rational quotCoef = _dividend->getLeadCoef() / divisor.getLeadCoef();
        // Multiply the divisor's lower poly by the monomial (quotCoef)X^(quotOrder):
        PVmulMonoVis mulMono(quotCoef, quotOrder);
        divisor.getLowerPoly().accept(mulMono);
        APolyV* prod = mulMono.result();
        // Subtract prod from the dividend's lower poly to obtain the reduced dividend:   
        APolyV* diff = (static_cast<const ANonConstPolyV*>(_dividend))->getLowerPoly() 
            - *prod;
        // Recursively perform long division on diff:
        _dividend = diff;
        divisor.accept(*this);
        _quotient = new NonConstPolyCV(quotCoef, quotOrder, *_quotient); 
        delete prod;
        delete diff;
    }
}
