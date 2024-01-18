// File: HashData/HashData.hpp

#ifndef HASHDATA_HPP_
#define HASHDATA_HPP_

#include <iostream> // ostream.
#include <string> // string.
#include <functional>
#include "ArrayT.hpp"
#include "ListL.hpp"
#include "CAMetrics.hpp"
#include "HashFunctions.hpp"
using namespace std;

// ========= HashTable =========

class HashTable {
private:
    ArrayT<shared_ptr<ListL<CAMetricsStr>>> _ht; // ht is the hash table array.
    HashFunction _hashFunction;

public:
    // Post: Creates a hash table with cap slots, initialized to be empty
    // and hash function specified by hashFunction.
    HashTable(int cap, HashFunction hashFunction) : _ht(cap), _hashFunction(hashFunction) {
        for (int i = 0; i < cap; i++)
            _ht[i] = make_shared<ListL<CAMetricsStr>>();
    }

    // Post: If x is not in the chain, installs x in the hash table
    // at the beginning of the appropriate chain.
    void insert(CAMetricsStr const &x) {
        _ht[_hashFunction(x) % _ht.cap()]->prepend(x);
    }

    // Post: Returns true if this hash table contains x.
    bool contains(CAMetricsStr const &x) const {
        return _ht[_hashFunction(x) % _ht.cap()]->contains(x);
    }

    // Post: Sends the entire hash table to os. For each index of the
    // hash table that contains a nonempty chain, outputs that index
    // followed by ": " followed by the chain.
    void toStream(ostream &os) const {
        for (int i = 0; i < _ht.cap(); i++) {
            if (!_ht[i]->isEmpty()) {
                cout << i << ": ";
                _ht[i]->toStream(cout);
                cout << endl;
            }
        }
    }
};

// ========= operator<< =========

ostream &operator<<(ostream &os, HashTable const &rhs) {
    rhs.toStream(os);
    return os;
}

#endif
