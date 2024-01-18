// File: BiTreeCSV/BiTCSVpreOrderVis.hpp

#ifndef BiTCSV_ZPREORDERVIS_HPP_
#define BiTCSV_ZPREORDERVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVpreOrderVis =========
template<class T>
class BiTCSVpreOrderVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    // ========= Constructor =========
    BiTCSVpreOrderVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A preorder representation of this tree is sent to os.
    void emptyCase(BiTreeCSV<T> &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        _os << host.root() << "  ";
        host.left()->accept(*this);
        host.right()->accept(*this);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        _os << host.root() << "  ";
        host.left()->accept(*this);
        host.right()->accept(*this);
    }
};

// Global function for convenience
template<class T>
void preOrder(ostream &os, BiTreeCSV<T> const &tree) {
    BiTCSVpreOrderVis<T> preOrderVis(os);
    tree.accept(preOrderVis);
}

#endif
