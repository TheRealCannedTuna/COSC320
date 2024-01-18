// File: PolyV/APolyV.cpp

#include "APolyV.hpp"
#include "APolyVVis.hpp"
#include "PVwriteStreamVis.hpp"
#include "PVevalVis.hpp"
#include "PVaddVis.hpp"
#include "PVmulConstVis.hpp"
#include "PVmulVis.hpp"
#include "PVlongDivVis.hpp"

void AConstPolyV::accept(APolyVVis &visitor) const {
    visitor.visitConstPolyV(*this);
}

void ANonConstPolyV::accept(APolyVVis& visitor) const {
    visitor.visitNonConstPolyV(*this);
}

Rational APolyV::operator()(const Rational &r) const {
    PVevalVis evalVis(r);
    this->accept(evalVis);
    return evalVis.result();
}

ostream &operator <<(ostream &os, APolyV const &poly) {
    PVwriteStreamVis ws(os);
    poly.accept(ws);
    return os;
}

APolyV* operator+(APolyV const &lhs, APolyV const &rhs) {
    PVaddVis addVis(&rhs);
    lhs.accept(addVis);
    return addVis.result();
}

APolyV* operator-(APolyV const &lhs, APolyV const &rhs) {    
    APolyV* negRhs = -1 * rhs;
    APolyV* result = lhs + *negRhs;
    delete negRhs;  // collect garbage
    return result;
}

APolyV* operator-(APolyV const &rhs) {    
    return (-1 * rhs);
}

APolyV* operator*(Rational const &r, APolyV const &rhs) {
    PVmulConstVis mcv(r);
    rhs.accept(mcv);
    return mcv.result();
}

APolyV* operator*(APolyV const &lhs, APolyV const &rhs) {
    PVmulVis mulVis(&rhs);
    lhs.accept(mulVis);
    return mulVis.result();
}

APolyV* operator/(APolyV const &dividend, APolyV const &divisor) {
    PVlongDivVis longDiv(&dividend);
    divisor.accept(longDiv);
    return longDiv.getQuotient();
}

APolyV* operator%(APolyV const &dividend, APolyV const &divisor) {
    PVlongDivVis longDiv(&dividend);
    divisor.accept(longDiv);
    return longDiv.getRemainder();    
}
