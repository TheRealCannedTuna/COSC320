// File: PolyVisitor/Add.cpp

#include "Add.hpp"
#include "Polynomial.hpp"

AObject* Add::forConst(Polynomial* pLHS, AObject* pRHS) {
    APolyAlgo* pAddConst = new AddConst(pLHS->getLeadCoef());
    Polynomial* pRHSPoly = dynamic_cast<Polynomial*>(pRHS); 
    AObject* pResult = pRHSPoly->execute(pAddConst, nullptr);
    delete pAddConst;
    pAddConst = nullptr;
    return pResult;
}

AObject* Add::forNonConst(Polynomial* pLHS, AObject* pRHS) {
    APolyAlgo* pAddMono = new AddMono(pLHS->getLeadCoef(), pLHS->iGetOrder());
    Polynomial* pRHSPoly = dynamic_cast<Polynomial*>(pRHS);
    AObject* pTempPoly = pRHSPoly->execute(pAddMono, nullptr);
    AObject* pResult = pLHS->getLowerPoly().execute(this, pTempPoly);
    delete pAddMono;
    pAddMono = nullptr;
    delete pTempPoly;
    pTempPoly = nullptr;
    return pResult;
}

AddConst::AddConst(const Rational &rat): _coef(rat) {
}

AObject* AddConst::forConst(Polynomial* pPoly, AObject*) {
    return new Polynomial(_coef + pPoly->getLeadCoef());
}

AObject* AddConst::forNonConst(Polynomial* pPoly, AObject*) {
    Polynomial* pTempPoly = dynamic_cast<Polynomial*>(pPoly->getLowerPoly().execute(this, nullptr));
    AObject* pResult = new Polynomial(pPoly->getLeadCoef(), pPoly->iGetOrder(), *pTempPoly);
    delete pTempPoly;
    pTempPoly = nullptr;
    return pResult;
}

AddMono::AddMono(const Rational &coef, int iOrder): _coef(coef), _iOrder(iOrder) {
}

AObject* AddMono::forConst(Polynomial* pPoly, AObject* ) {
    return new Polynomial(_coef, _iOrder, Polynomial(pPoly->getLeadCoef()));
}

AObject* AddMono::forNonConst(Polynomial* pPoly, AObject* ) {
    Rational polyCoef = pPoly->getLeadCoef();
    int iPolyOrder = pPoly->iGetOrder();
    if (iPolyOrder < _iOrder) {
        return new Polynomial(_coef, _iOrder, *pPoly);
    }
    else if (iPolyOrder == _iOrder) {
        return new Polynomial(_coef + polyCoef, _iOrder, pPoly->getLowerPoly());
    }
    else {  // _iOrder < iPolyOrder
        Polynomial* pTempPoly = dynamic_cast<Polynomial*>(pPoly->getLowerPoly().execute(this, nullptr));
        AObject* pResult = new Polynomial(polyCoef, iPolyOrder, *pTempPoly);
        delete pTempPoly;
        pTempPoly = nullptr;
        return pResult;
    }
}

