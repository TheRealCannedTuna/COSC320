// File: ListCSV/LCSVremLastVis.hpp

#ifndef LCSVREMLASTVIS_HPP_
#define LCSVREMLASTVIS_HPP_

#include <iostream>

#include "ListCSV.hpp"

using namespace std;

template<class T> class LCSVremLastHelperVis; // Forward declaration.

// ========= LCSVremLastVis =========
template<class T>
class LCSVremLastVis : public AListCSVVis<T> {
private:
    T _result; // Output result.

public:
    // ========= Constructor =========
    LCSVremLastVis() = default;

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        cerr << "LCSVremLastVis: list is empty." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        LCSVremLastHelperVis<T> remLastHelperVis(host);
        host.rest()->accept(remLastHelperVis);
        _result = remLastHelperVis.result();
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVremLastVis precondition violated: "
             << "Cannot remove last from a const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVremLastVis precondition violated: "
             << "Cannot remove last from a const list." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Pre: This list is not empty.
    // Post: The last element is removed from this list and returned.
    T result() const {
        return _result;
    }
};

// ========= LCSVremLastHelperVis =========
template<class T>
class LCSVremLastHelperVis : public AListCSVVis<T> {
private:
    ListCSV<T> &_previous; // Input parameter.
    T _result; // Output result.

public:
    // ========= Constructor =========
    explicit LCSVremLastHelperVis(ListCSV<T> &previous): _previous(previous) {}

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        _result = _previous.remFirst();
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        LCSVremLastHelperVis<T> remLastHelper(host);
        host.rest()->accept(remLastHelper);
        _result = remLastHelper.result();
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "SmartLCSVremLastHelperVis precondition violated: "
             << "Cannot remove last from a const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "SmartLCSVremLastHelperVis precondition violated: "
             << "Cannot remove last from a const list." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Pre: previous.rest() is the host list.
    // Post: The last element of previous is removed and returned.
    T const &result() const {
        return _result;
    }
};

// Global function for convenience.
template<class T>
T remLast(ListCSV<T> &list) {
    LCSVremLastVis<T> remLastVis;
    list.accept(remLastVis);
    return remLastVis.result();
}

#endif
