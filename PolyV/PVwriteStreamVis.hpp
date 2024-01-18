/* 
 * File:   PVwriteStreamVis.hpp
 * Author: dxnguyen
 *
 * Created on January 24, 2013, 10:08 PM
 */

#ifndef PVWRITESTREAMVIS_HPP
#define PVWRITESTREAMVIS_HPP

#include <iostream>
#include "APolyVVis.hpp"

class PVwriteStreamVis : public APolyVVis {
private:
    ostream &_os;

public:

    PVwriteStreamVis(ostream &os) : _os(os) {}
    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);
    ostream &result() {
        return _os;
    }
};

#endif

