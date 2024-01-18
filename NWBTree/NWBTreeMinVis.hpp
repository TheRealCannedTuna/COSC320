c// File: NWBTree/NWBTreeMinVis.hpp

#ifndef NWBTreeMINVIS_HPP_
#define NWBTreeMINVIS_HPP_

#include <iostream>

#include "ANTreeVis.hpp"
#include "NTreeIsEmptyVis.hpp"

using namespace std;

// ========= NWBTreeMinVis =========

template<class T>
class NWBTreeMinVis : public ANTreeVis<T> {
private:
    T _result; // Output result.

public:
    // ========= Constructor =========
    NWBTreeMinVis() = default;

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            cerr << "NWBTreeMinVis: empty tree has no minimum." << endl;
            throw -1;
        }
        default:
        {
            if (isEmpty(*host.getChild(0))) {
                _result = host.getData(0);
            } else {
                host.getChild(0)->accept(*this);
            }
            break;

        }
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        switch (size) {
        case 0:
        {
            cerr << "NWBTreeMinVis: empty tree has no minimum." << endl;
            throw -1;
        }
        default:
        {
            if (isEmpty(*host.getChild(0))) {
                _result = host.getData(0);
            } else {
                host.getChild(0)->accept(*this);
            }
            break;

        }

        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Pre: The host tree is not empty.
    // Post: The minimum value of the tree is returned.

    T result() const {
        return _result;
    }
};

// Global function for convenience

template<class T>
T min(NTree<T> const &tree) {
    NWBTreeMinVis<T> minVis;
    tree.accept(minVis);
    return minVis.result();
}

#endif
