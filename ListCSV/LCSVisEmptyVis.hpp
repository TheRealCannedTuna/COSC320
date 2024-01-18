// File: ListCSV/LCSVisEmptyVis.hpp

#ifndef LCSVISEMPTYVIS_HPP_
#define LCSVISEMPTYVIS_HPP_

#include "ListCSV.hpp"

// ========= LCSVisEmptyVis =========
template<class T>
class LCSVisEmptyVis : public AListCSVVis<T> {
private:
    bool _result; // Output result.

public:
    // ========= Constructor =========
    LCSVisEmptyVis() = default;

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        _result = true;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        _result = false;
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        _result = true;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        _result = false;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if the host list is empty; Otherwise, false is returned.
    bool result() const {
        return _result;
    }
};

// Global function for convenience.
template<class T>
bool isEmpty(ListCSV<T> const &list) {
    LCSVisEmptyVis<T> isEmptyVis;
    list.accept(isEmptyVis);
    return isEmptyVis.result();
}

#endif
