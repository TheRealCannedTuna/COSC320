// File: BiTreeCSV/BiTCSVheightVis.hpp

#ifndef BiTCSV_ZHEIGHTVIS_HPP_
#define BiTCSV_ZHEIGHTVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVheightVis =========
template<class T>
class BiTCSVheightVis : public ABiTreeCSVVis<T> {
private:
    int _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVheightVis() = default;

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _result = 0;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        BiTCSVheightVis<T> heightLeft;
        BiTCSVheightVis<T> heightRight;
        host.left()->accept(heightLeft);
        host.right()->accept(heightRight);
        _result = heightLeft.result() > heightRight.result() ? 1 + heightLeft.result() : 1 + heightRight.result();
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _result = 0;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        BiTCSVheightVis<T> heightLeft;
        BiTCSVheightVis<T> heightRight;
        host.left()->accept(heightLeft);
        host.right()->accept(heightRight);
        _result = heightLeft.result() > heightRight.result() ? 1 + heightLeft.result() : 1 + heightRight.result();
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The height of the host tree is returned.
    int result() const {
        return _result;
    }
};

// Global function for convenience
template<class T>
int height(BiTreeCSV<T> const &tree) {
    BiTCSVheightVis<T> biTcsVheightVis;
    tree.accept(biTcsVheightVis);
    return biTcsVheightVis.result();
}

#endif
