// File: Polynomial/PolyNode.hpp

#ifndef PolyNode_hpp
#define PolyNode_hpp

#include "PolynomialC.hpp"
#include "Rational.hpp"

class APolyNode {
private:
    APolyNode &operator=(APolyNode const &rhs);  //Disabled.
public:
    virtual int getOrder() const = 0;
    virtual Rational getLeadCoef() const = 0;
    virtual PolynomialC getLowerPoly() const = 0;
    virtual Rational eval(Rational const &r, Rational const &acc) const = 0;
    virtual APolyNode* clone(void) const = 0;
    virtual PolynomialC addNode(APolyNode const * pNode) const = 0;
    virtual PolynomialC addConst(Rational const &coef) const = 0;
    virtual PolynomialC addMono(Rational const &coef, int iExp) const = 0;
    // Pre: exp >=1.

    virtual void writeStream(ostream &os) const = 0 ;
    virtual void readStream(PolynomialC &poly, istream &is) = 0;
    // Pre: poly is the owner of this APolyNode.
};

class ConstNode: public APolyNode {
private:
    Rational _coef;
    ConstNode &operator=(ConstNode const &rhs);  //Disabled.

public:
    ConstNode(Rational const &coef = 0);
    ConstNode(ConstNode const &rhs);
    virtual int getOrder() const override;
    virtual Rational getLeadCoef() const override;
    virtual PolynomialC getLowerPoly() const override;
    virtual Rational eval(Rational const &r, Rational const &acc) const override;
    virtual APolyNode* clone(void) const override;
    virtual PolynomialC addNode(APolyNode const *pNode) const override;
    virtual PolynomialC addConst(Rational const &coef) const override;
    virtual PolynomialC addMono(Rational const &coef, int iExp) const override;
    virtual void writeStream(ostream &os) const override;
    virtual void readStream(PolynomialC &poly, istream &is) override;
};

class NonConstNode: public APolyNode {
private:
    Rational _coef;
    int _order;             // Degree of node >= 1.
    PolynomialC _lowerPoly; // Lower order polynomial.

    NonConstNode &operator =(const NonConstNode &rhs);  //not implemented to disallow usage.

public:
    NonConstNode(Rational const &coef, int order);
    NonConstNode(Rational const &coef, int order, const PolynomialC &lowerPoly);
    NonConstNode(const NonConstNode &rhs);
    virtual int getOrder() const override;
    virtual Rational getLeadCoef() const override;
    virtual PolynomialC getLowerPoly() const override;
    virtual Rational eval(Rational const &r, Rational const &acc) const override;
    virtual APolyNode* clone(void) const override;
    virtual PolynomialC addNode(APolyNode const * pNode) const override;
    virtual PolynomialC addConst(Rational const &coef) const override;
    virtual PolynomialC addMono(Rational const &coef, int iExp) const override;
    virtual void writeStream(ostream &os) const override;
    virtual void readStream(PolynomialC &poly, istream &is) override;
};

#endif
