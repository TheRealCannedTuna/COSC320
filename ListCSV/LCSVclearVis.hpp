// File: ListCSV/LCSVclearVis.hpp

#ifndef LCSVCLEARVIS_HPP_
#define LCSVCLEARVIS_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

// ========= LCSVclearVis =========
template<class T>
class LCSVclearVis : public AListCSVVis<T> {
public:
    // ========= Constructor =========
    LCSVclearVis() = default;

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: This list is cleared to the empty list.
    void emptyCase(ListCSV<T> &host) override {
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        host.rest()->accept(*this);
        host.remFirst();
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVclearVis precondition violated: "
             << "Cannot clear a const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVclearVis precondition violated: "
             << "Cannot clear a const list." << endl;
        throw -1;
    }
};

// Global function for convenience.
// Post: list is cleared to the empty list.
template<class T>
void clear(ListCSV<T> &list) {
    LCSVclearVis<T> clearVis;
    list.accept(clearVis);
}

#endif
