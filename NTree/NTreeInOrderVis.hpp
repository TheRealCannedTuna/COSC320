// File: NTree/NTreeInOrderVis.hpp

#ifndef NTreeINORDERVIS_HPP_
#define NTreeINORDERVIS_HPP_

#include <iostream>

#include "ANTreeVis.hpp"
#include "NTree.hpp"

using namespace std;

// ========= NTreeInOrderVis =========
template<class T>
class NTreeInOrderVis : public ANTreeVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    // ========= Constructor =========
    NTreeInOrderVis(ostream &os) :
        _os(os) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T>& host) override {
        switch (size) {
        case 0:
        {
            break;
        }
        default:
        {
            host.getChild(0)->accept(*this);
            for (int i = 0; i < size; i++) {
                _os << host.getData(i) << "  ";
                host.getChild(i + 1)->accept(*this);
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
            break;
        }
        default:
        {
            host.getChild(0)->accept(*this);
            for (int i = 0; i < size; i++) {
                _os << host.getData(i) << "  ";
                host.getChild(i + 1)->accept(*this);
            }
            break;
        }
        }
    }
};

// Global function for convenience
template<class T>
void inOrder(ostream &os, NTree<T> const &tree) {
    NTreeInOrderVis<T> inOrderVis(os);
    tree.accept(inOrderVis);
}

#endif
