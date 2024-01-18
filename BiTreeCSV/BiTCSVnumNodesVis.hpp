// File: BiTreeCSV/BiTCSVnumNodesVis.hpp

#ifndef BiTCSV_ZNUMNODESVIS_HPP_
#define BiTCSV_ZNUMNODESVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVnumNodesVis =========
template<class T>
class BiTCSVnumNodesVis : public ABiTreeCSVVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVnumNodesVis():
        _result(0) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        host.left()->accept(*this);
        host.right()->accept(*this);
        _result++;
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        host.left()->accept(*this);
        host.right()->accept(*this);
        _result++;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The number of nodes of the host tree is returned.
    int result() const {
        return _result;
    }
};

// Global function for convenience
template<class T>
int numNodes(BiTreeCSV<T> const &tree) {
    BiTCSVnumNodesVis<T> numNodesVis;
    tree.accept(numNodesVis);
    return numNodesVis.result();
}

#endif
