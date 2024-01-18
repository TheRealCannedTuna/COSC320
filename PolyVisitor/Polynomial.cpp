// File: PolyVisitor/Polynomial.cpp

#include <cassert>
#include "Polynomial.hpp"
#include "PolyNode.hpp"
#include "WriteStream.hpp"
#include "ReadStream.hpp"
#include "Add.hpp"

// ========= Constructors =========
Polynomial::Polynomial(const Rational &coef, int order) {
    assert(order >= 0);
    if (0 == order || coef == Rational(0)) {
        _headNode = new ConstNode(coef); //a constant polynomial
    }
    else {
        _headNode = new NonConstNode(coef, order, Polynomial());
    }
}

Polynomial::Polynomial(const Rational &coef, int iOrder, const Polynomial &lowerOrderTerms) {
    if (Rational(0) == coef) {
        _headNode = lowerOrderTerms._headNode->clone();
    }
    else {
        assert(iOrder > lowerOrderTerms.iGetOrder());
        _headNode = new NonConstNode(coef, iOrder, lowerOrderTerms);
    }
}

Polynomial::Polynomial(const Polynomial &poly) {
    _headNode = poly._headNode->clone();
}

ConstNode::ConstNode(const Rational &coef) {
    _coef = coef;
}

ConstNode::ConstNode(const ConstNode &rhs) {
    _coef = rhs._coef;
}

NonConstNode::NonConstNode(const Rational &coef, int iOrder):
    _coef(coef), 
    _iOrder(iOrder), 
    _lowerPoly() {
}

NonConstNode::NonConstNode(const Rational &coef, int iOrder, const Polynomial &lowerPoly):
    _coef(coef), 
    _iOrder(iOrder), 
    _lowerPoly(lowerPoly) {
}

NonConstNode::NonConstNode(const NonConstNode &rhs):
    _coef(rhs._coef), 
    _iOrder(rhs._iOrder), 
    _lowerPoly(rhs._lowerPoly) {
}

// ========= Destructors =========
Polynomial::~Polynomial() {
    delete _headNode;
    _headNode = nullptr;
}

// ========= Assignment =========
Polynomial &Polynomial::operator=(const Polynomial &rhs) {
    if (&rhs == this) {
        return *this;
    }
    delete _headNode;
    _headNode = rhs._headNode->clone();
    return *this;
}

// ========= iGetOrder =========
int Polynomial::iGetOrder() const { return _headNode->iGetOrder(); }

int ConstNode::iGetOrder() const { return 0; }

int NonConstNode::iGetOrder() const { return _iOrder; }

// ========= getLeadCoef =========
Rational Polynomial::getLeadCoef() const { return _headNode->getLeadCoef(); }

Rational ConstNode::getLeadCoef() const { return _coef; }

Rational NonConstNode::getLeadCoef() const { return _coef; }

// ========= getLowerPoly =========
Polynomial Polynomial::getLowerPoly() const { return _headNode->getLowerPoly(); }

Polynomial ConstNode::getLowerPoly() const {
    assert(false);
    return Polynomial();
}

Polynomial NonConstNode::getLowerPoly() const { return _lowerPoly; }

// ========= execute =========
AObject* Polynomial::execute(APolyAlgo* pAlgo, AObject* inp) {
    return _headNode->execute(pAlgo, inp, this); 
}

AObject* ConstNode::execute(APolyAlgo* pAlgo, AObject* inp, Polynomial* pOwner) {
    return pAlgo->forConst(pOwner, inp);
}

AObject* NonConstNode::execute(APolyAlgo* pAlgo, AObject* inp, Polynomial* pOwner) {
    return pAlgo->forNonConst(pOwner, inp);
}

// ========= clone =========
APolyNode* ConstNode::clone(void) const {
    return new ConstNode(_coef);
}

APolyNode* NonConstNode::clone() const {
    return new NonConstNode(_coef, _iOrder, _lowerPoly);
}

// ========= Polynomial input/output =========
ostream &operator <<(ostream &os, const Polynomial &poly) {
    Polynomial temp(poly); // avoid const.
    APolyAlgo* pWS = new WriteStream(os);
    temp.execute(pWS, nullptr);
    delete pWS;
    pWS = nullptr; // pWS is well-defined.
    return os;
}

istream &operator >>(istream &is, Polynomial &poly) {
    APolyAlgo* pRS = new ReadStream(is);
    poly.execute(pRS, nullptr);
    delete pRS;
    pRS = nullptr;// pRS is well-defined.
    return is;
}

Polynomial operator +(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial tempLHS(lhs);
    Polynomial tempRHS(rhs);
    APolyAlgo* pAdd = new Add;
    Polynomial* pSum = dynamic_cast <Polynomial*>(tempLHS.execute(pAdd, &tempRHS));
    delete pAdd;
    pAdd = nullptr;
    Polynomial result(*pSum);  // make a copy of the sum.
    delete pSum;
    pSum = nullptr;
    return result;
}
