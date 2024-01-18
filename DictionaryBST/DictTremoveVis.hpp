// File: DictionaryBST/DictTremoveVis.hpp

#ifndef DICTTREMOVEVIS_HPP_
#define DICTTREMOVEVIS_HPP_

#include <iostream>
using namespace std;

#include "ADictionary.hpp"
#include "BiTreeCSV.hpp"
#include "BiTCSVisEmptyVis.hpp"

// ========= DictTremoveVis =========

template <class K, class V>
class DictTremoveVis : public ABiTreeCSVVis< DictPair<K, V> > {
private:
    K const &_key; // Input parameter.
    V _val; // Output result.
    bool _found; // Output result.

public:
    // ========= Constructor =========

    DictTremoveVis(K const &key) : _key(key) {}

    // ========= visit =========

    void emptyCase(BiTreeCSV< DictPair<K, V> > &host) override {
        _found = false;
    }

    void nonEmptyCase(BiTreeCSV< DictPair<K, V> > &host) override {
        if (_key < host.root().key()) {
            host.left()->accept(*this);
        } else if (_key > host.root().key()) {
            host.right()->accept(*this);
        } else {
            _val = host.root().val();
            auto maxLeft = host.left();
            if (isEmpty(*host.left())) {
                host.remRoot();
                return;
            }
            while (!isEmpty(*maxLeft->right())) {
                maxLeft = maxLeft->right();
            }
            host.root() = maxLeft->root();
            maxLeft->remRoot();
            _found = true;
        }
    }

    // ========= visit const =========

    void emptyCase(BiTreeCSV< DictPair<K, V> > const &host) override {
        cerr << "DictTremoveVis precondition violated: "
             << "Cannot remove from a const tree." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV< DictPair<K, V> > const &host) override {
        cerr << "DictTremoveVis precondition violated: "
             << "Cannot remove from a const tree." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.
    // The host dictionary does not contain key and its associated value.

    bool result(V &val) const {
        if (_found) {
            val = _val;
        }
        return _found;
    }
};

#endif
