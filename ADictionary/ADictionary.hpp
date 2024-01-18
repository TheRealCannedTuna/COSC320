// File: DictionaryTemplate/ADictionary.hpp

#ifndef ADICTIONARY_HPP_
#define ADICTIONARY_HPP_

#include <iostream>
using namespace std;

// ========= DictPair =========
template <class K, class V>
class DictPair {
    // Pre: K and V have default constructor, copy constructor, operator=, operator<<.
    // K has comparison operators for searching.
    // Note: Copy constructor and operator= for DictPair are automatically generated.

private:
    K _key;
    V _val;
public:
    DictPair(K key, V const &val) :
        _key(key),
        _val(val) {
    }

    K const &key() const {
        return _key;
    }

    V const &val() const {
        return _val;
    }

    void setVal(V const &val) {
        _val = val;
    }
};

// ========= operator<< =========
template <class K, class V>
ostream &operator<<(ostream &os, DictPair<K, V> const &rhs) {
    os << "<" << rhs.key() << ", " << rhs.val() << ">";
    return os;
}

// ========= ADictionary =========
template <class K, class V>
class ADictionary {
public:
    virtual ~ADictionary() = default;

    virtual void clear() = 0;

    virtual void insert(K const &key, V const &val) = 0;
    // Post: This dictionary contains key and its associated value, val,
    // without duplicate keys.

    virtual bool remove(K const &key, V &val) = 0;
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.
    // This dictionary does not contain key and its associated value.

    virtual bool contains(K const &key, V &val) const = 0;
    // Post: If key is found, then val is the associated value, and true is returned;
    // otherwise false is returned.

    virtual void toStream(ostream &os) const = 0;
};

// ========= operator<< =========
template<class K, class V>
ostream &operator<<(ostream &os, const ADictionary<K, V> &rhs) {
    rhs.toStream(os);
    return os;
}

#endif
