// File: BiTreeCSV/BiTCSVequalsVis.hpp

#ifndef BiTCSV_ZEQUALSVIS_HPP_
#define BiTCSV_ZEQUALSVIS_HPP_

#include <iostream>

#include "BiTreeCSV.hpp"
#include "BiTCSVisEmptyVis.hpp"

using namespace std;

template<class T> class BiTCSVequalsHelperVis; // Forward declaration.

// ========= BiTCSVequalsVis =========
template<class T>
class BiTCSVequalsVis : public ABiTreeCSVVis<T> {
private:
    BiTreeCSV<T> const &_rhs; // Input parameter.
    bool _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVequalsVis(BiTreeCSV<T> const &rhs):
        _rhs(rhs) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _result = isEmpty(_rhs);
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
//        from BiTreeCS.hpp
//
//        if (rhs.isEmpty() || _data != rhs.root()) return false;
//        if (!_left->isEmpty() && rhs.left()->isEmpty() || _left->isEmpty() && !rhs.left()->isEmpty())
//            return false;
//        if (!_right->isEmpty() && rhs.right()->isEmpty() || _right->isEmpty() && !rhs.right()->isEmpty())
//            return false;
//        return _left->equals(*rhs.left()) && _right->equals(*rhs.right());

        if (isEmpty(_rhs) || host.root() != _rhs.root())
            _result = false;
        else if (!isEmpty(*host.left()) && isEmpty(*_rhs.left()) || isEmpty(*host.left()) && !isEmpty(*host.left()))
            _result = false;
        else if (!isEmpty(*host.right()) && isEmpty(*_rhs.right()) || isEmpty(*host.right()) && !isEmpty(*host.right()))
            _result = false;
        else {
            BiTCSVequalsVis<T> rightRhsTree(*_rhs.right());
            BiTCSVequalsVis<T> leftRhsTree(*_rhs.left());
            host.left()->accept(leftRhsTree);
            host.right()->accept(rightRhsTree);
            _result = leftRhsTree.result() && rightRhsTree.result();
        }
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _result = isEmpty(_rhs);
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
//        BiTCSVequalsHelperVis biTcsVequalsHelperVis(host, _rhs);
        if (isEmpty(_rhs) || host.root() != _rhs.root())
            _result = false;
        else if (!isEmpty(*host.left()) && isEmpty(*_rhs.left()) || isEmpty(*host.left()) && !isEmpty(*host.left()))
            _result = false;
        else if (!isEmpty(*host.right()) && isEmpty(*_rhs.right()) || isEmpty(*host.right()) && !isEmpty(*host.right()))
            _result = false;
        else {
            BiTCSVequalsVis<T> rightRhsTree(*_rhs.right());
            BiTCSVequalsVis<T> leftRhsTree(*_rhs.left());
            host.left()->accept(leftRhsTree);
            host.right()->accept(rightRhsTree);
            _result = leftRhsTree.result() && rightRhsTree.result();
        }    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: true is returned if the host tree is equal to rhs;
    // otherwise, false is returned.
    // Two trees are equal if they contain the same number of equal elements
    // with the same shape.
    bool result() const {
        return _result;
    }
};

// ========= BiTCSVequalsHelperVis =========
template<class T>
class BiTCSVequalsHelperVis : public ABiTreeCSVVis<T> {
private:
    T const &_data; // Input parameter.
    BiTreeCSV<T> const &_left; // Input parameter.
    BiTreeCSV<T> const &_right; // Input parameter.
    bool _result; // Output result.

public:
    // ========= Constructor =========
    BiTCSVequalsHelperVis(T const &data, BiTreeCSV<T> const &left, BiTreeCSV<T> const &right):
        _data(data), _left(left), _right(right) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        cerr << "BiTCSVequalsHelperVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        cerr << "BiTCSVequalsHelperVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVequalsHelperVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVequalsHelperVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: true is returned if root equals host.root(),
    // left equals host.left(), and right equals host.right();
    // otherwise, false is returned.
    bool result() const {
        cerr << "BiTCSVequalsHelperVis: Exercise for the student." << endl;
        throw -1;
    }
};

// Global function for convenience.
// ========= operator== =========
template<class T>
bool operator==(BiTreeCSV<T> const &lhs, BiTreeCSV<T> const &rhs) {
    BiTCSVequalsVis<T> biTcsVequalsVis(rhs);
    lhs.accept(biTcsVequalsVis);
    return biTcsVequalsVis.result();
}

#endif
