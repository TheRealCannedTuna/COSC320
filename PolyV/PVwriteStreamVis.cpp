#include "PVwriteStreamVis.hpp"

class PVwriteLowerPolyVis : public APolyVVis {
private:
    ostream &_os;

public:

    PVwriteLowerPolyVis(ostream &os) : _os(os) {
    }

    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);
};

void PVwriteStreamVis::visitConstPolyV(AConstPolyV const &host) {
    _os << host.getLeadCoef();
}

void PVwriteStreamVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    if (host.getLeadCoef() == 1) {
        _os << "x";  // output x instead of 1x
    }
    else if (host.getLeadCoef() == -1) {
        _os << "-x";
    }
    else {
        _os << host.getLeadCoef() << "x";
    }
    if (host.getOrder() != 1) {
        _os << "^" << host.getOrder();  // output Rx instead of Rx^1
    }
    PVwriteLowerPolyVis writeLowerVis(_os);
    host.getLowerPoly().accept(writeLowerVis);
}

void PVwriteLowerPolyVis::visitConstPolyV(AConstPolyV const &host) {
    if (host.getLeadCoef() < 0) {
        _os << " - " << -host.getLeadCoef();
    } 
    else if (host.getLeadCoef() > 0) {
        _os << " + " << host.getLeadCoef();
    }
}

void PVwriteLowerPolyVis::visitNonConstPolyV(ANonConstPolyV const &host) {
    if (host.getLeadCoef() < 0) {
        _os << " - ";
        if (host.getLeadCoef() != -1) {
            _os << -host.getLeadCoef();
        }
    } 
    else { // host.getLeadCoef() > 0
        _os << " + ";
        if (host.getLeadCoef() != 1) {
            _os << host.getLeadCoef();
        }
    }
    _os << "x";
    if (host.getOrder() != 1) {
        _os << "^" << host.getOrder();
    }
    host.getLowerPoly().accept(*this);
}
