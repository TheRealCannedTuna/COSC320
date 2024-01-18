// File: BiTreeCSV/BiTCSVcontainsVis.hpp

#ifndef BiTCSV_ZCONTAINSVIS_HPP_
#define BiTCSV_ZCONTAINSVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVcontainsVis =========
template<class T>
class BiTCSVcontainsVis : public ABiTreeCSVVis<T> {
private:
    T _data; // Input parameter.
    bool _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVcontainsVis(T data):
        _data(data) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _result = false;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        _result = host.root() == _data;
        if (!_result) {
            host.left()->accept(*this);
        }
        if (!_result) {
            host.right()->accept(*this);
        }
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _result = false;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        _result = host.root() == _data;
        if (!_result) {
            host.left()->accept(*this);
        }
        if (!_result) {
            host.right()->accept(*this);
        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: true is returned if val is contained in this tree;
    // otherwise, false is returned.
    bool result() const {
        return _result;
    }
};

// Global function for convenience
template<class T>
bool contains(T data, BiTreeCSV<T> const &tree) {
    BiTCSVcontainsVis<T> biTcsVcontainsVis(data);
    tree.accept(biTcsVcontainsVis);
    return biTcsVcontainsVis.result();
}

#endif
