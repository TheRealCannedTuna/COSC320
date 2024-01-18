
// File:   APolyV.hpp
/**
 * Abstract polynomial taxonomy.
 */

#ifndef APOLYV_HPP
#define APOLYV_HPP

#include "Rational.hpp"

class APolyVVis; // Forward declaration of visitor interface.

/**
 * Abstract polynomial using visitor.
 */
class APolyV {
private:
    APolyV &operator=(const APolyV &rhs); //not implemented to disallow usage.
    APolyV(APolyV const &rhs); //not implemented to disallow usage.
    
public:

    APolyV() {}
    virtual ~APolyV() {}
    virtual int getOrder() const = 0;
    virtual Rational getLeadCoef() const = 0;
    virtual void accept(APolyVVis &visitor) const = 0;
    virtual APolyV *clone() const = 0;
    // Post: A pointer to a copy of this polynomial is returned.    
    Rational operator()(const Rational &r) const;
    // Overload the function call operator to evaluate the target polynomial
    // at the given Rational r.
};

/**
 * Abstract constant polynomial.
 */
class AConstPolyV : public APolyV {
private:
    AConstPolyV &operator=(const AConstPolyV &rhs); //not implemented to disallow usage.
    AConstPolyV (AConstPolyV const &rhs);  //not implemented to disallow usage.
    
public:

    AConstPolyV() {}
    virtual ~AConstPolyV() {}

    virtual int getOrder() const {
        return 0;
    }
    virtual void accept(APolyVVis &visitor) const;
};

/**
 * Abstract non-constant polynomial.
 */
class ANonConstPolyV : public APolyV {
private:
    ANonConstPolyV &operator=(const ANonConstPolyV &rhs); //not implemented to disallow usage.
    ANonConstPolyV(ANonConstPolyV const &rhs); //not implemented to disallow usage.
    
public:

    ANonConstPolyV() {}
    virtual ~ANonConstPolyV() {}
    virtual APolyV const &getLowerPoly() const = 0; // TODO: pointer needed for polymorphic behavior???   
    virtual void accept(APolyVVis &visitor) const;
};

ostream &operator <<(ostream &os, APolyV const &poly);
APolyV* operator+(APolyV const &lhs, APolyV const &rhs);
APolyV* operator-(APolyV const &lhs, APolyV const &rhs);
APolyV* operator-(APolyV const &rhs); // unary minus
APolyV* operator*(Rational const &r, APolyV const &rhs);  // multiplication by a constant Rational
APolyV* operator*(APolyV const &lhs, APolyV const &rhs);
APolyV* operator/(APolyV const &dividend, APolyV const &divisor); // return the quotient of dividend/divisor
APolyV* operator%(APolyV const &dividend, APolyV const &divisor); // return the remainder of dividend/divisor

#endif

