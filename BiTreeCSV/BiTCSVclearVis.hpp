// File: BiTreeCSV/BiTCSVclearVis.hpp

#ifndef BiTCSV_ZCLEARVIS_HPP_
#define BiTCSV_ZCLEARVIS_HPP_

#include <iostream>
using namespace std;

#include "BiTreeCSV.hpp"

// ========= BiTCSVclearVis =========
template<class T>
class BiTCSVclearVis : public ABiTreeCSVVis<T> {
public:
    // ========= Constructor =========
    BiTCSVclearVis() = default;

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: This tree is cleared to the empty tree.
    void emptyCase(BiTreeCSV<T> &host) override {
        // the tree is already empty
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        host.left()->accept(*this);
        host.right()->accept(*this);
        host.remRoot();
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVclearVis precondition violated: "
             << "Cannot clear a const tree." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVclearVis precondition violated: "
             << "Cannot clear a const tree." << endl;
        throw -1;
    }
};

// Global function for convenience
template<class T>
void clear(BiTreeCSV<T> &tree) {
    BiTCSVclearVis<T> biTcsVclearVis;
    tree.accept(biTcsVclearVis);
}

#endif
