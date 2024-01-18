// File: ListCSV/LCSVappendVis.hpp

#ifndef LCSVAPPENDVIS_HPP_
#define LCSVAPPENDVIS_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

// ========= LCSVappendVis =========
template<class T>
class LCSVappendVis : public AListCSVVis<T> {
private:
    T const &_data; // Input parameter.

public:
    // ========= Constructor =========
    explicit LCSVappendVis(T const &data): _data(data) {}

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: data is appended to this list.

    void emptyCase(ListCSV<T> &host) override {
        host.prepend(_data);
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        host.rest()->accept(*this);
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVappendVis precondition violated: "
             << "Cannot append const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVappendVis precondition violated: "
             << "Cannot append const list." << endl;
        throw -1;
    }
};

// Global function for convenience.
// Post: data is appended to list.
template<class T>
void append(ListCSV<T> &list, T const &data) {
    LCSVappendVis<T> appendVis(data);
    list.accept(appendVis);
}

#endif
