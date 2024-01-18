// File: NWBTree/NWBTreeContainsVis.hpp

#ifndef NWBTreeContainsVis_HPP_
#define NWBTreeContainsVis_HPP_

#include <iostream>

#include "ANTreeVis.hpp"

using namespace std;

// ========= NWBTreeContainsVis =========
template<class T>
class NWBTreeContainsVis : public ANTreeVis<T> {
private:
    T _val; // Input parameter.
    int _result; // Output result.

public:
    // ========= Constructor =========
    NWBTreeContainsVis(T val) : _val(val) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            _result = -1;
            break;
        }
        default:
        {
            int k = 0;
            while (k < size && host.getData(k) < _val) {
                k++;
            }
            if (k < size && host.getData(k) == _val) {
                _result = k;
            } else {
                host.getChild(k)->accept(*this);
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
            _result = -1;
            break;
        }
        default:
        {
            int k = 0;
            while (k < size && host.getData(k) < _val) {
                k++;
            }
            if (k < size && host.getData(k) == _val) {
                _result = k;
            } else {
                host.getChild(k)->accept(*this);
            }
            break;

        }
        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The position of val in its node is returned if val is contained in this tree;
    // otherwise, -1 is returned.

    int result() const {
        return _result;
    }
};

// Global function for convenience

template<class T>
int contains(T key, NTree<T> const &tree) {
    NWBTreeContainsVis<T> containsVis(key);
    tree.accept(containsVis);
    return containsVis.result();
}

#endif
