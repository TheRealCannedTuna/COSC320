// File:   APolyVVis.hpp
/** 
 * Visitor interface for APolyV.
 */

#ifndef APOLYVVIS_HPP
#define APOLYVVIS_HPP

#include "APolyV.hpp"

class APolyVVis {
public:
    virtual ~APolyVVis() {}
    virtual void visitConstPolyV(AConstPolyV const &host) = 0;
    virtual void visitNonConstPolyV(ANonConstPolyV const &host) = 0;
};

#endif  /* APOLYVVIS_HPP */

