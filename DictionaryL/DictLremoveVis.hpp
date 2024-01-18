// File: DictionaryL/DictLremoveVis.hpp

#ifndef LCSVREMOVEVIS_HPP_
#define LCSVREMOVEVIS_HPP_

#include "ADictionary.hpp"
#include "ListCSV.hpp"

// ========= DictLremoveVis =========
template < class K, class V>
class DictLremoveVis: public AListCSVVis< DictPair<K, V> > {
private:
    K const &_key; // Input parameter.
    V _val; // Output result.
    bool _found; // Output result.

public:
    // ========= Constructor =========
    DictLremoveVis(K const &key): _key(key) {}

    // ========= visit =========
    void emptyCase(ListCSV< DictPair<K, V> > &host) override {
        _found = false;
    }

    void nonEmptyCase(ListCSV< DictPair<K, V> > &host) override {
        if (_key == host.first().key()) {
            _val = host.first().val();
            _found = true;
            host.remFirst();
        }
        else {
            host.rest()->accept(*this);
        }
    }

    // ========= visit const =========
    void emptyCase(ListCSV< DictPair<K, V> > const &host) override {
        cerr << "DictLremoveVis precondition violated: "
             << "Cannot remove from a const list." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV< DictPair<K, V> > const &host) override {
        cerr << "DictLremoveVis precondition violated: "
             << "Cannot remove from a const list." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.
    // The host dictionary does not contain key and its associated value.
    bool result(V &val) const {
        val = _val;
        return _found;
    }
};

#endif
