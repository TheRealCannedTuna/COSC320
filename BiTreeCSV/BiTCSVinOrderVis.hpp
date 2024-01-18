// File: BiTreeCSV/BiTCSVinOrderVis.hpp

#ifndef BITINORDERVIS_HPP_
#define BITINORDERVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVinOrderVis =========
template<class T>
class BiTCSVinOrderVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input paramter.

public:
    // ========= Constructor =========
    BiTCSVinOrderVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A inOrder representation of this tree is sent to os.
    void emptyCase(BiTreeCSV<T> &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        host.left()->accept(*this);
        _os << host.root() << "  ";
        host.right()->accept(*this);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        host.left()->accept(*this);
        _os << host.root() << "  ";
        host.right()->accept(*this);
    }
};

// Global function for convenience
template<class T>
void inOrder(ostream &os, BiTreeCSV<T> const &tree) {
    BiTCSVinOrderVis<T> biTcsVinOrderVis(os);
    tree.accept(biTcsVinOrderVis);
}

#endif
