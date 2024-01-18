// File: ListCSV/LCSVcontainsVis.hpp

#ifndef LCSVCONTAINSVIS_HPP_
#define LCSVCONTAINSVIS_HPP_

#include <iostream>
using namespace std;

#include "ListCSV.hpp"

// ========= LCSVcontainsVis =========
template<class T>
class LCSVcontainsVis : public AListCSVVis<T> {
private:
    T const &_data; // Input parameter.
    bool _result;   // Output result.

public:
    // ========= Constructor =========
    explicit LCSVcontainsVis(T const &data): _data(data) {}

    // ========= visit =========
    void emptyCase(ListCSV<T> &host) override {
        _result = false;
    }

    void nonEmptyCase(ListCSV<T> &host) override {
        if (host.first() == _data) {
            _result = true;
            return;
        }
        host.rest()->accept(*this);
    }

    // ========= visit const =========
    void emptyCase(ListCSV<T> const &host) override {
        _result = false;
    }

    void nonEmptyCase(ListCSV<T> const &host) override {
        if (host.first() == _data) {
            _result = true;
            return;
        }
        host.rest()->accept(*this);
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if data is contained in the host list;
    // Otherwise, false is returned.
    bool result() const {
        return _result;
    }
};

// Global function for convenience.
// Post: true is returned if data is contained in list;
// Otherwise, false is returned.
template<class T>
bool contains(ListCSV<T> const &list, T const &data) {
    LCSVcontainsVis containsVis(data);
    list.accept(containsVis);
    return containsVis.result();
}

#endif
