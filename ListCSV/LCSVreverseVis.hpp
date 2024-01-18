// File: ListCSV/LCSVreverseVis.hpp

#ifndef LCSVREVERSEVIS_HPP_
#define LCSVREVERSEVIS_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

template<class T> class LCSVreverseHelperVis; // Forward declaration.

// ========= LCSVreverseVis =========
template<class T>
class LCSVreverseVis : public AListCSVVis<T> {

public:
    // ========= Constructor =========
    LCSVreverseVis() = default;

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: The host list is reversed.
    void emptyCase(ListCSV<T> &host) override {
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        ListCSV<T> revList;
        LCSVreverseHelperVis<T> reverseHelperVis(revList);
        host.accept(reverseHelperVis);
        host = revList;
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVreverseVis precondition violated: "
             << "Cannot reverse const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVreverseVis precondition violated: "
             << "Cannot reverse const list." << endl;
        throw -1;
    }
};

// ========= LCSVreverseHelperVis =========
template<class T>
class LCSVreverseHelperVis : public AListCSVVis<T> {
private:
    ListCSV<T> &_revList; // Input parameter, modified by visitor.

public:
    // ========= Constructor =========
    explicit LCSVreverseHelperVis(ListCSV<T> &revList): _revList(revList) {}

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: The host list is prepended to revList in reverse order,
    // and the host list is empty.
    void emptyCase(ListCSV<T> &host) override {
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        _revList.prepend(host.remFirst());
        host.accept(*this);
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVreverseHelperVis precondition violated: "
             << "Cannot reverse const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVreverseHelperVis precondition violated: "
             << "Cannot reverse const list." << endl;
        throw -1;
    }
};

// Global function for convenience.
template<class T>
void reverse(ListCSV<T> &list) {
    LCSVreverseVis<T> reverseVis;
    list.accept(reverseVis);
}

#endif
