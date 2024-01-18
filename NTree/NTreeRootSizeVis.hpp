// File: NTree/NTreeRootSizeVis.hpp

#ifndef NTreeROOTSIZEVIS_HPP_
#define NTreeROOTSIZEVIS_HPP_

#include "ANTreeVis.hpp"

// ========= NTreeRootSizeVis =========

template<class T>
class NTreeRootSizeVis : public ANTreeVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    NTreeRootSizeVis(): _result(-1) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T>& host) override {
        _result = size;
    }

    // ========= visit const =========
    void caseAt(int size, NTree<T> const &host) override {
        _result = size;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The size of the root of the host tree is returned.
    // The root size of an empty tree is 0.

    int result() const {
        return _result;
    }
};

// Global function for convenience
template<class T>
int rootSize(NTree<T> const &tree) {
    NTreeRootSizeVis<T> rootSizeVis;
    tree.accept(rootSizeVis);
    return rootSizeVis.result();
}

#endif
