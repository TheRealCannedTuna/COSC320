// File: ListCSV/LCSVconcatVis.hpp

#ifndef SMARTLCSVCONCATVIS_HPP
#define SMARTLCSVCONCATVIS_HPP

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

// ========= LCSVconcatVis (copy concatenate) =========
template<class T>
class LCSVconcatVis : public AListCSVVis<T> {
private:
    ListCSV<T> &_suffix; // Input parameter, modified by visitor.

public:
    // ========= Constructor =========
    explicit LCSVconcatVis(ListCSV<T> &suffix): _suffix(suffix) {}

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: suffix is appended to the host list.
    // suffix is empty (cut concatenate, as opposed to copy concatenate).
    void emptyCase(ListCSV<T> &host) override {
        cerr << "LCSVconcatVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        cerr << "LCSVconcatVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVconcatVis precondition violated: "
             << "Cannot concatenate const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVconcatVis precondition violated: "
             << "Cannot concatenate const list." << endl;
        throw -1;
    }
};

// Global function for convenience.
// Post: suffixList is appended to list.
// suffixList is empty (cut concatenate, as opposed to copy concatenate).
template<class T>
void concat(ListCSV<T> &list, ListCSV<T> &suffixList) {
    cerr << "concat: Exercise for the student." << endl;
    throw -1;
}

#endif
