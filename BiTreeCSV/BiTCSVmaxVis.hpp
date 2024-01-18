// File: BiTreeCSV/BiTCSVmaxVis.hpp

#ifndef BiTCSV_ZMAXVIS_HPP_
#define BiTCSV_ZMAXVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"

using namespace std;

// ========= BiTCSVmaxVis =========
/**
 * Computes the max element value in the host tree.
 * @tparam T is totally ordered by operator>.
 */

template<class T>
class BiTCSVmaxVis : public ABiTreeCSVVis<T> {
private:
    shared_ptr<const T> _result;  // similar to the raw pointer semantic: _result is a (shared) pointer to a const T.

public:
    // ========= Constructor =========
    BiTCSVmaxVis() = default;

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        cerr << "BiTCSVmaxVis precondition violated: "
             << "An empty tree has no maximum." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        shared_ptr<const T> rootData = make_shared<T>(host.root());
        shared_ptr<const T> leftMax = (isEmpty(*host.left())) ?
            rootData : (host.left()->accept(*this), _result);
        shared_ptr<const T> rightMax = (isEmpty(*host.right())) ?
            rootData : (host.right()->accept(*this), _result);

        _result = (*leftMax > *rightMax) ?
            ((*leftMax > *rootData) ? leftMax : rootData) :
            ((*rightMax > *rootData) ? rightMax : rootData);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVmaxVis precondition violated: "
             << "An empty tree has no maximum." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        shared_ptr<const T> rootData = make_shared<T>(host.root());
        shared_ptr<const T> leftMax = (isEmpty(*host.left())) ?
            rootData : (host.left()->accept(*this), _result);
        shared_ptr<const T> rightMax = (isEmpty(*host.right())) ?
            rootData : (host.right()->accept(*this), _result);

        _result = (*leftMax > *rightMax) ?
            ((*leftMax > *rootData) ? leftMax : rootData) :
            ((*rightMax > *rootData) ? rightMax : rootData);
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: The maximum element of the host tree is returned.
    T const &result() const {
        return *_result;
    }
};

// Global function for convenience
template<class T>
T const &max(BiTreeCSV<T> const &tree) {
    BiTCSVmaxVis<T> maxVis;
    tree.accept(maxVis);
    return maxVis.result();
}

#endif
