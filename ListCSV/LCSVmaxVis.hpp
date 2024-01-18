// File: ListCSV/LCSVmaxVis.hpp

#ifndef LCSVMAXVIS_HPP_
#define LCSVMAXVIS_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

template<class T> class LCSVmaxHelperVis; // Forward declaration.

// ========= LCSVmaxVis =========
/**
 * Computes the max element value in the host list.
 * @tparam T is totally ordered by operator>.
 */

template<class T>
class LCSVmaxVis : public AListCSVVis<T> {
private:
    shared_ptr<const T> _result;  // Output result.

public:
    // ========= Constructor =========
    LCSVmaxVis() = default;

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        cerr << "max precondition violated: An empty list has no maximum." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        LCSVmaxHelperVis<T> maxHelperVis(host.first());
        host.rest()->accept(maxHelperVis);
        _result = maxHelperVis.result();
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        cerr << "max precondition violated: An empty list has no maximum." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        LCSVmaxHelperVis<T> maxHelperVis(host.first());
        host.rest()->accept(maxHelperVis);
        _result = maxHelperVis.result();
    }

    // ========= result =========
    // Pre: This LCSVmaxVis visitor has been accepted by a host list.
    // Pre: This list is not empty.
    // Post: The maximum element of this list is returned.
    T const &result() const {
        return (*_result);
    }
};

// ========= LCSVmaxHelperVis =========
template<class T>
class LCSVmaxHelperVis : public AListCSVVis<T> {
private:
    T const &_val; // Input parameter.
    shared_ptr<const T> _result; // Output result.

public:
    // ========= Constructor =========
    explicit LCSVmaxHelperVis(T const &val):
        _val(val) {
    }

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        _result = make_shared<const T>(_val);
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        if (host.first() > _val) {
            LCSVmaxHelperVis<T> maxHelperVis(host.first());
            host.rest()->accept(maxHelperVis);
            _result = maxHelperVis.result();
        }
        else {
            LCSVmaxHelperVis<T> maxHelperVis(_val);
            host.rest()->accept(maxHelperVis);
            _result = maxHelperVis.result();
        }
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        _result = make_shared<const T>(_val);
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        if (host.first() > _val) {
            LCSVmaxHelperVis<T> maxHelperVis(host.first());
            host.rest()->accept(maxHelperVis);
            _result = maxHelperVis.result();
        }
        else {
            LCSVmaxHelperVis<T> maxHelperVis(_val);
            host.rest()->accept(maxHelperVis);
            _result = maxHelperVis.result();
        }
    }

    // ========= result =========
    // Pre: This LCSVmaxHelperVis visitor has been accepted by a host list.
    // Post: A shared_ptr of the maximum element of this list is returned.
    shared_ptr<const T> result() const {
        return _result;
    }
};

// Global function for convenience.
template<class T>
T const max(ListCSV<T> const &list) {
    LCSVmaxVis<T> maxVis;
    list.accept(maxVis);
    return maxVis.result();
}

#endif
