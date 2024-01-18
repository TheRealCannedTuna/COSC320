// File: DictionaryHash/DictHinsertVis.hpp

#ifndef DICTHINSERTVIS_HPP
#define DICTHINSERTVIS_HPP

#include "ADictionary.hpp"
#include "ListCSV.hpp"

// ========= DictHinsertVis =========
template < class K, class V>
class DictHinsertVis: public AListCSVVis<DictPair<K, V>> {
private:
    K const &_key; // Input parameter.
    V const &_val; // Input parameter.

public:
    // ========= Constructor =========
    DictHinsertVis(K const &key, V const &val):
        _key(key),
        _val(val) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host list.
    // Post: The host dictionary contains key and its associated value, val,
    // without duplicate keys.
    void emptyCase(ListCSV<DictPair<K, V>> &host) override {
        host.prepend(DictPair<K, V>(_key, _val));
    }

    void nonEmptyCase(ListCSV<DictPair<K, V>> &host) override {
        if (_key == host.first().key()) {
            host.first() = (DictPair<K, V>(_key, _val));
        }
        else {
            host.rest()->accept(*this);
        }
    }

    // ========= visit const =========
    void emptyCase(ListCSV< DictPair<K, V> > const &host) override {
        cerr << "DictHinsertVis precondition violated: "
             << "Cannot insert into a const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV< DictPair<K, V> > const &host) override {
        cerr << "DictHinsertVis precondition violated: "
             << "Cannot insert into a const list." << endl;
        throw -1;
    }
};

#endif  /* DICTHINSERTVIS_HPP */
