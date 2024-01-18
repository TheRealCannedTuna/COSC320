/* 
 * File:   PVaddVis.hpp
 * Author: dxnguyen
 *
 * Created on February 2, 2013, 10:18 PM
 */

#ifndef PVADDVIS_HPP
#define PVADDVIS_HPP

#include "APolyVVis.hpp"

class PVaddVis : public APolyVVis {
private:
    APolyV const *_rhs;
    APolyV *_result;  //owned by this visitor

private:
    PVaddVis(const PVaddVis& rhs); // disabled
    PVaddVis &operator=(PVaddVis const &rhs); // disabled

public:

    PVaddVis(APolyV const *rhs) : _rhs(rhs) {
    }

    virtual ~PVaddVis() {
        delete _result;
        _result = nullptr;
    }

    APolyV* result() {
        return _result->clone();  // the caller owns the requested result and is responsible for garbage collection.
    }

    virtual void visitConstPolyV(AConstPolyV const &host);
    virtual void visitNonConstPolyV(ANonConstPolyV const &host);

};

#endif  /* PVADDVIS_HPP */

