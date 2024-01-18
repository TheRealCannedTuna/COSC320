// File: DictionaryL/DictLcontainsVis.hpp

#ifndef DICTLCONTAINSVIS_HPP_
#define DICTLCONTAINSVIS_HPP_

#include <iostream>
using namespace std;

#include "ADictionary.hpp"
#include "ListCSV.hpp"

// ========= DictLcontainsVis =========
template <class K, class V>
class DictLcontainsVis : public AListCSVVis< DictPair<K,V> > {
private:
    K const &_key; // Input parameter.
    V _val; // Output result.
    bool _found; // Output result.

public:
    // ========= Constructor =========
    DictLcontainsVis(K const &key): _key(key) {}

    // ========= visit =========
    void emptyCase(ListCSV< DictPair<K,V> > &host) override {
        cerr << "DictLcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV< DictPair<K,V> > &host) override {
        cerr << "DictLcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= visit const =========
    void emptyCase(ListCSV< DictPair<K,V> > const &host) override {
        cerr << "DictLcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV< DictPair<K, V> > const &host) override {
        cerr << "DictLcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.
    bool result(V &val) const {
        cerr << "DictLcontainsVis: Exercise for the student." << endl;
        throw -1;
    }
};

#endif
