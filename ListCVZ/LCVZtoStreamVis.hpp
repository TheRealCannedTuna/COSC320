//
// Created by Dung Nguyen on 8/3/21.
//

#ifndef DP4DSDISTRIBUTION_LCVZTOSTREAM_HPP
#define DP4DSDISTRIBUTION_LCVZTOSTREAM_HPP

#include <iostream>
#include "AListCVZVis.hpp"
#include "ListCVZ.hpp"
using namespace std;

// ========= LCVZtoStreamHelperVis =========
template<class T>
class LCVZtoStreamHelperVis : public AListCVZVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    LCVZtoStreamHelperVis(ostream &os);
    shared_ptr<void> visitMTList(AListCVZ<T> const &host) override;
    shared_ptr<void> visitNEList(AListCVZ<T> const &host) override;
};

// ========= Constructor =========
template<class T>
LCVZtoStreamHelperVis<T>::LCVZtoStreamHelperVis(ostream &os): _os(os) {
}

// ========= visit =========
template<class T>
shared_ptr<void> LCVZtoStreamHelperVis<T>::visitMTList(AListCVZ<T> const &) {
    _os << ")";
    return nullptr;
}

template<class T>
shared_ptr<void> LCVZtoStreamHelperVis<T>::visitNEList(AListCVZ<T> const &host) {
    _os << ", " << host.first();
    host.rest()->accept(*this);
    return nullptr;
}

// ========= LCVZtoStreamVis =========
template<class T>
class LCVZtoStreamVis : public AListCVZVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    LCVZtoStreamVis(ostream &os);
    shared_ptr<void> visitMTList(AListCVZ<T> const  &host) override;
    shared_ptr<void> visitNEList(AListCVZ<T> const  &host) override;
};

// ========= Constructor =========
template<class T>
LCVZtoStreamVis<T>::LCVZtoStreamVis(ostream &os): _os(os) {
}

// ========= visit =========
template<class T>
shared_ptr<void> LCVZtoStreamVis<T>::visitMTList(AListCVZ<T> const  &) {
    _os << "()";
    return nullptr;
}

template<class T>
shared_ptr<void> LCVZtoStreamVis<T>::visitNEList(AListCVZ<T> const  &host) {
    _os << "(" << host.first();
    LCVZtoStreamHelperVis<T> toStreamHVis(_os);
    host.rest()->accept(toStreamHVis);
    return nullptr;
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, shared_ptr<const AListCVZ<T>> rhs) {
    static LCVZtoStreamVis<T> toStreamVis(os); // static for efficiency.
    rhs->accept(toStreamVis);
    return os;
}

#endif //DP4DSDISTRIBUTION_LCVZTOSTREAM_HPP
