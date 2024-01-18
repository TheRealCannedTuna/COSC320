// File: BiTreeCSV/BiTCSVisEmptyVis.hpp

#ifndef BiTCSV_ZISEMPTYVIS_HPP_
#define BiTCSV_ZISEMPTYVIS_HPP_

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVisEmptyVis =========
template<class T>
class BiTCSVisEmptyVis : public ABiTreeCSVVis<T> {
private:
    bool _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVisEmptyVis() = default;

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _result = true;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        _result = false;
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _result = true;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        _result = false;
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
bool isEmpty(BiTreeCSV<T> const &tree) {
    BiTCSVisEmptyVis<T> isEmptyVis;
    tree.accept(isEmptyVis);
    return isEmptyVis.result();
}

#endif
