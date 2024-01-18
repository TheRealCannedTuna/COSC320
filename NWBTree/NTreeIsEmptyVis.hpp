// File: NWBTree/NTreeIsEmptyVis.hpp

#ifndef NTreeIsEmptyVis_HPP_
#define NTreeIsEmptyVis_HPP_

#include <iostream>

#include "ANTreeVis.hpp"

using namespace std;

// ========= NTreeIsEmptyVis =========
template<class T>
class NTreeIsEmptyVis : public ANTreeVis<T> {
private:
    bool _result; // Output result.

public:
    // ========= Constructor =========
    NTreeIsEmptyVis() = default;

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
        case 0:
        {
            _result = true;
            break;
        }
        default:
        {
            _result = false;
            break;
        }
        }
    }

    // ========= visit const =========
    void caseAt(int size, NTree<T> const &host) override {
        switch (size) {
        case 0:
        {
            _result = true;
            break;
        }
        default:
        {
            _result = false;
            break;
        }
        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: true is returned if the host tree is empty;
    // otherwise, false is returned.

    bool result() const {
        return _result;
    }
};

// Global function for convenience

template<class T>
bool isEmpty(NTree<T> const &tree) {
    NTreeIsEmptyVis<T> emptyVis;
    tree.accept(emptyVis);
    return emptyVis.result();
}

#endif
