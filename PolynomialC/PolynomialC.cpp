// File: Polynomial/PolynomialC.cpp

#include <cassert>

#include "PolynomialC.hpp"
#include "PolyNode.hpp"

// ========= Constructors =========
PolynomialC::PolynomialC(Rational const &coef, int order) {
    assert(order >= 0);
    if (0 == order || coef == Rational(0)) {
        _headNode = new ConstNode(coef); //a constant polynomial
    }
    else {
        _headNode = new NonConstNode(coef, order, PolynomialC());
    }
}

PolynomialC::PolynomialC(Rational const &coef, int order, PolynomialC const &lowerOrderPoly) {
    if (Rational(0) == coef) {
        _headNode = lowerOrderPoly._headNode->clone();
    }
    else {
        assert(order > lowerOrderPoly.getOrder());
        _headNode = new NonConstNode(coef, order, lowerOrderPoly);
    }
}

PolynomialC::PolynomialC(PolynomialC const &poly) {
    _headNode = poly._headNode->clone();
}

ConstNode::ConstNode(Rational const &coef) {
    _coef = coef;
}

ConstNode::ConstNode(const ConstNode &rhs) {
    _coef = rhs._coef;
}

NonConstNode::NonConstNode(Rational const &coef, int order) :
    _coef(coef),
    _order(order),
    _lowerPoly() {
}

NonConstNode::NonConstNode(Rational const &coef, int order, PolynomialC const &lowerPoly) :
    _coef(coef),
    _order(order),
    _lowerPoly(lowerPoly) {
}

NonConstNode::NonConstNode(const NonConstNode &rhs) :
    _coef(rhs._coef),
    _order(rhs._order),
    _lowerPoly(rhs._lowerPoly) {
}

// ========= Destructors =========
PolynomialC::~PolynomialC() {
    delete _headNode;
    _headNode = nullptr;
}

// ========= Assignment =========
PolynomialC &PolynomialC::operator=(PolynomialC const &rhs) {
    if (&rhs == this) {
        return *this;
    }
    delete _headNode;
    _headNode = rhs._headNode->clone();
    return *this;
}

// ========= getOrder =========
int PolynomialC::getOrder() const {
    return _headNode->getOrder();
}

int ConstNode::getOrder() const {
    return 0;
}

int NonConstNode::getOrder() const {
    return _order;
}

// ========= getLeadCoef =========
Rational PolynomialC::getLeadCoef() const {
    return _headNode->getLeadCoef();
}

Rational ConstNode::getLeadCoef() const {
    return _coef;
}

Rational NonConstNode::getLeadCoef() const {
    return _coef;
}

// ========= getLowerPoly =========
PolynomialC PolynomialC::getLowerPoly() const {
    return _headNode->getLowerPoly();
}

PolynomialC ConstNode::getLowerPoly() const {
    assert(false);
    return PolynomialC();
}

PolynomialC NonConstNode::getLowerPoly() const {
    return _lowerPoly;
}

// ========= Polynomial evaluation, operator(), eval =========
Rational PolynomialC::operator()(Rational const &r) const {
    return _headNode->eval(r, 0);
}

Rational ConstNode::eval(Rational const &, Rational const &acc) const {
    return _coef + acc;
}

Rational NonConstNode::eval(Rational const &r, Rational const &acc) const {
    Rational temp = acc + _coef;
    for (int i = _lowerPoly.getOrder(); i < _order; i++) {
        temp  = temp * r;
    }
    return _lowerPoly._headNode->eval(r, temp);
}

// ========= Polynomial addition, operator +, add... =========
PolynomialC operator +(PolynomialC const &lhs, PolynomialC const &rhs) {
    return lhs._headNode->addNode(rhs._headNode);
}

PolynomialC ConstNode::addNode(const APolyNode* pNode) const {
    return pNode->addConst(_coef);
}

PolynomialC NonConstNode::addNode(const APolyNode* pNode) const {
    return _lowerPoly + pNode->addMono(_coef, _order);
}

PolynomialC ConstNode::addConst(Rational const &coef) const {
    return PolynomialC(_coef + coef);
}

PolynomialC NonConstNode::addConst(Rational const &coef) const {
    return PolynomialC(_coef, _order, _lowerPoly._headNode->addConst(coef));
}

PolynomialC ConstNode::addMono(Rational const &coef, int iExp) const {
    return PolynomialC(coef, iExp, PolynomialC(_coef));
}

PolynomialC NonConstNode::addMono(Rational const &coef, int iExp) const {
    if (_order < iExp) {
        return PolynomialC(coef, iExp, PolynomialC(_coef, _order, _lowerPoly));
    }
    else if (_order == iExp) {
        return PolynomialC(_coef + coef, _order, _lowerPoly);
    }
    else {  //(_order > iExp)
        return PolynomialC(_coef, _order, _lowerPoly._headNode->addMono(coef, iExp));
    }
}

// ========= Polynomial input, operator >>, readStream =========
istream &operator >>(istream &is, PolynomialC &poly) {
    poly._headNode->readStream(poly, is);
    return is;
}

void ConstNode::readStream(PolynomialC &poly, istream &is) {
    Rational coef = 0;
// read in a temp coef to make sure everything is OK first.
    if (is >> coef) {
        int iExp = 0;
        is >> iExp;
        if (0 != iExp) {
            PolynomialC lowerPoly;
            is >> lowerPoly;
            poly = PolynomialC(coef, iExp, lowerPoly);
        }
        else {
            _coef = coef;
        }
    }
}

void NonConstNode::readStream(PolynomialC &poly, istream &is) {
    Rational coef = 0;
// read in a temp coef to make sure everything is OK first.
    if (is >> coef) {
        int _iExp = 0;
        is >> _iExp;
        if (0 != _iExp) {
            PolynomialC lowerPoly;
            is >> lowerPoly;
            poly = PolynomialC(coef, _iExp, lowerPoly);
        }
        else {
            poly = PolynomialC(coef);
        }
    }
}

// ========= Polynomial output, operator <<, writeStream =========
ostream &operator <<(ostream &os, PolynomialC const &poly) {
    poly._headNode->writeStream(os);
    return os;
}

void ConstNode::writeStream(ostream &os) const {
    os << _coef << '\t' << 0 << endl;
}

void NonConstNode::writeStream(ostream &os) const {
    os << _coef << '\t' << _order << endl;
    os << _lowerPoly;
}

// ========= clone =========
APolyNode* ConstNode::clone(void) const {
    return new ConstNode(_coef);
}

APolyNode* NonConstNode::clone() const {
    return new NonConstNode(_coef, _order, _lowerPoly);
}
