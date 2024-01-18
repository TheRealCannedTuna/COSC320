// File: DictionaryHash/DictHcontainsVis.hpp

#ifndef DICTHCONTAINSVIS_HPP
#define DICTHCONTAINSVIS_HPP

#include <iostream>
#include "ADictionary.hpp"
#include "ListCSV.hpp"

using namespace std;

// ========= DictHcontainsVis =========
template <class K, class V>
class DictHcontainsVis : public AListCSVVis<DictPair<K, V>> {
private:
    K const &_key; // Input parameter.
    V _val; // Output result.
    bool _found; // Output result.

public:
    // ========= Constructor =========
    DictHcontainsVis(K const &key):
        _key(key) {
    }

    // ========= visit =========
    void emptyCase(ListCSV<DictPair<K, V>> &host) override {
        cerr << "DictHcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<DictPair<K, V>> &host) override {
        cerr << "DictHcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= visit const =========
    void emptyCase(ListCSV<DictPair<K, V>> const &host) override {
        cerr << "DictHcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    void nonEmptyCase(ListCSV<DictPair<K, V>> const &host) override {
        cerr << "DictHcontainsVis: Exercise for the student." << endl;
        throw -1;
    }

    // ========= result =========
    // Pre: This visitor has been accepted by a host list.
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.
    bool result(V &val) const {
        cerr << "DictHcontainsVis: Exercise for the student." << endl;
        throw -1;
    }
};

#endif  /* DICTHCONTAINSVIS_HPP */
