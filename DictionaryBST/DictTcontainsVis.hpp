// File: DictionaryBST/DictTcontainsVis.hpp

#ifndef DICTTCONTAINSVIS_HPP_
#define DICTTCONTAINSVIS_HPP_

#include <iostream>
using namespace std;

#include "ADictionary.hpp"
#include "BiTreeCSV.hpp"

// ========= DictTcontainsVis =========
template <class K, class V>
class DictTcontainsVis : public ABiTreeCSVVis< DictPair<K, V> > {
private:
    K const &_key; // Input parameter.
    V _val; // Output result.
    bool _found; // Output result.

public:
    // ========= Constructor =========
    DictTcontainsVis(K const &key) : _key(key) {}

    // ========= visit =========
    void emptyCase(BiTreeCSV< DictPair<K, V> > &host) override {
        _found = false;
    }

    void nonEmptyCase(BiTreeCSV< DictPair<K, V> > &host) override {
        if (_key > host.root().key()) {
            host.right()->accept(*this);
        } else if (_key < host.root().key()) {
            host.left()->accept(*this);
        } else {
            _val = host.root().val();
            _found = true;
        }
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV< DictPair<K, V> > const &host) override {
        _found = false;
    }

    void nonEmptyCase(BiTreeCSV< DictPair<K, V> > const &host) override {
        if (_key > host.root().key()) {
            host.right()->accept(*this);
        } else if (_key < host.root().key()) {
            host.left()->accept(*this);
        } else {
            _val = host.root().val();
            _found = true;
        }
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.
    bool result(V &val) const {
        if (_found) {
            val = _val;
        }
        return _found;
    }
};

#endif
