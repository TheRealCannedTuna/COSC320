// File: ListCSV/LCSVtoStreamVis.hpp

#ifndef LCSVTOSTREAM_HPP_
#define LCSVTOSTREAM_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

template<class T> class LCSVtoStreamHelperVis; // Forward declaration.

// ========= LCSVtoStreamVis =========
template<class T>
class LCSVtoStreamVis : public AListCSVVis<T> {
private:
    ostream &_os; // Output parameter.

public:
    // ========= Constructor =========
    explicit LCSVtoStreamVis(ostream &os): _os(os) {}

    // ========= visit =========
    // Pre: This LCSVtoStreamVis visitor has been accepted by a host list.
    // Post: A string representation of this list is returned.
    void emptyCase(ListCSV<T> &host) override {
        _os << "()";
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        _os << "(" << host.first();
        LCSVtoStreamHelperVis<T> toStreamHVis(_os);
        host.rest()->accept(toStreamHVis);
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        _os << "()";
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        _os << "(" << host.first();
        LCSVtoStreamHelperVis<T> toStreamHelperVis(_os);
        host.rest()->accept(toStreamHelperVis);
    }
};

// ========= LCSVtoStreamHelperVis =========
template<class T>
class LCSVtoStreamHelperVis : public AListCSVVis<T> {
private:
    ostream &_os; // Output parameter.

public:
    // ========= Constructor =========
    explicit LCSVtoStreamHelperVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This LCSVtoStreamHelperVis visitor has been accepted by a host list.
    // Post: A string representation of this list is returned
    // except for the leading open parenthesis "(", which is omitted.
    void emptyCase(ListCSV<T> &host) override {
        _os << ")";
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        _os << ", " << host.first();
        host.rest()->accept(*this);
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        _os << ")";
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        _os << ", " << host.first();
        host.rest()->accept(*this);
    }
};

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, ListCSV<T> const &rhs) {
    LCSVtoStreamVis<T> toStreamVis(os);
    rhs.accept(toStreamVis);
    return os;
}

#endif
