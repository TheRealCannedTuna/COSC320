// File: BiTreeCSV/BiTCSV_ZremLeaves.hpp

#ifndef BiTCSV_ZREMLEAVESVIS_HPP_
#define BiTCSV_ZREMLEAVESVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"
#include "BiTCSVisEmptyVis.hpp"

using namespace std;

// ========= BiTCSVremLeavesVis =========
template<class T>
class BiTCSVremLeavesVis : public ABiTreeCSVVis<T> {
public:
    // ========= Constructor =========
    BiTCSVremLeavesVis() = default;

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The leaves are removed from the host tree.
    void emptyCase(BiTreeCSV<T> &host) override {
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        if (isEmpty(*host.left()) && isEmpty(*host.right())) {
            // is a leaf node
            host.remRoot();
        } else {
            host.left()->accept(*this);
            host.right()->accept(*this);
        }
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVremLeavesVis precondition violated: "
             << "Cannot remove leaves from a const tree." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVremLeavesVis precondition violated: "
             << "Cannot remove leaves from a const tree." << endl;
        throw -1;
    }
};

// Global function for convenience
template<class T>
void remLeaves(BiTreeCSV<T> &tree) {
    BiTCSVremLeavesVis<T> biTcsVremLeavesVis;
    tree.accept(biTcsVremLeavesVis);
}

template<class T>
void remLeaves(BiTreeCSV<T> const &tree) {
    BiTCSVremLeavesVis<T> biTcsVremLeavesVis;
    tree.accept(biTcsVremLeavesVis);
}

#endif
