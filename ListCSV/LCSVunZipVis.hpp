// File: ListCSV/LCSVunZipVis.hpp

#ifndef LCSVUNZIPVIS_HPP_
#define LCSVUNZIPVIS_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

// ========= LCSVunZipVis =========
template<class T>
class LCSVunZipVis : public AListCSVVis<T> {
private:
    shared_ptr<ListCSV<T>> _result; // Output result.

public:
    // ========= Constructor =========
    LCSVunZipVis() = default;

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        cerr << "LCSVunZipVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        cerr << "LCSVunZipVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVunZipVis precondition violated: "
             << "Cannot unZip const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        cerr << "LCSVunZipVis precondition violated: "
             << "Cannot unZip const list." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: The host list is every other element of the host list
    // starting with the first.
    // A pointer to a list with every other element of the host list
    // starting with the second is returned.
    shared_ptr<ListCSV<T>> result() const {
        cerr << "LCSVunZipVis: Exercise for the student." << endl;
        throw -1;
    }
};

// Global function for convenience.
// Post: list is every other element of list starting with the first.
// A pointer to a list with every other element of list starting
// with the second is returned.
template<class T>
shared_ptr<ListCSV<T>> unZip(ListCSV<T> &list) {
    cerr << "unZip: Exercise for the student." << endl;
    throw -1;
}

#endif
