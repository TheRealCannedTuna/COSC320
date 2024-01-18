// File: PolyVisitor/PolyNode.hpp

#ifndef PolyNode_hpp
#define PolyNode_hpp

#include "Rational.hpp"
#include "Polynomial.hpp"

class APolyNode {
    APolyNode &operator=(const APolyNode &rhs); //not implemented to disallow usage.
public:
    virtual int iGetOrder() const = 0;
    virtual Rational getLeadCoef() const = 0;
    virtual Polynomial getLowerPoly() const = 0;
    virtual AObject* execute(APolyAlgo* pAlgo, AObject* inp, Polynomial* pOwner) = 0;
    virtual APolyNode* clone(void) const = 0;  // due to lack of garbage collection.
};

class ConstNode: public APolyNode {
private:
    Rational _coef;
    ConstNode &operator=(const ConstNode &rhs);  //not implemented to disallow usage.

public:
    ConstNode(const Rational &coef = 0);
    ConstNode(const ConstNode &rhs);
    virtual int iGetOrder() const;
    virtual Rational getLeadCoef() const;
    virtual Polynomial getLowerPoly() const;
    virtual AObject* execute(APolyAlgo* pAlgo, AObject* inp, Polynomial* pOwner);
    virtual APolyNode* clone(void) const;
};

class NonConstNode: public APolyNode {
private:
    Rational _coef;
    int _iOrder;                 // degree of node >= 1.
    Polynomial _lowerPoly;  //lower order polynomial.

    NonConstNode &operator =(const NonConstNode &rhs);  //not implemented to disallow usage.

public:
    NonConstNode(const Rational &coef, int iOrder);
    NonConstNode(const Rational &coef, int iOrder, const Polynomial &lowerPoly);
    NonConstNode(const NonConstNode &rhs);
    virtual int iGetOrder() const;
    virtual Rational getLeadCoef() const;
    virtual Polynomial getLowerPoly() const;
    virtual AObject* execute(APolyAlgo* pAlgo, AObject* inp, Polynomial* pOwner);
    virtual APolyNode* clone(void) const;
};

#endif
