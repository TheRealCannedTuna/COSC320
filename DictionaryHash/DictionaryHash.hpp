// File: Hash/Hash.hpp

#ifndef DICTIONARYHASH_HPP
#define DICTIONARYHASH_HPP

#include <iostream> // ostream.
#include <string> // string.
#include <functional>
using namespace std;

#include "CAMetrics.hpp"
#include "HashFunctions.hpp"
#include "ADictionary.hpp"
#include "ArrayT.hpp"
#include "ListCSV.hpp"
#include "LCSVclearVis.hpp"
#include "LCSVisEmptyVis.hpp"
#include "LCSVtoStreamVis.hpp"
#include "DictHcontainsVis.hpp"
#include "DictHinsertVis.hpp"
#include "DictHremoveVis.hpp"

// ========= DictionaryHash =========

template <class K, class V>
class DictionaryHash : public ADictionary<K, V> {
private:
    ArrayT<shared_ptr<ListCSV<DictPair<K,V>>>> _hashTable;
    HashFunction _hashFunction;

public:
    DictionaryHash(int cap, HashFunction hashFunction) :
        _hashTable(cap),
        _hashFunction(hashFunction) {
        for (int i = 0; i < cap; i++)
            _hashTable[i] = make_shared<ListCSV<DictPair<K,V>>>();
    }

    void clear() override {
        LCSVclearVis<DictPair<K,V>> clearVis;
        for (int i = 0; i < _hashTable.cap(); i++)
            _hashTable[i]->accept(clearVis);
    }

    void insert(K const &key, V const &val) override {
        cerr << "HashTable::insert: Exercise for the student." << endl;
        throw -1;
    }

    bool remove(K const &key, V &val) override {
        DictHremoveVis<K, V> removeVis(key);
        _hashTable[_hashFunction(key) % _hashTable.cap()]->accept(removeVis);
        return removeVis.result(val);
    }

    bool contains(K const &key, V &val) const override {
        cerr << "HashTable::contains: Exercise for the student." << endl;
        throw -1;
    }

    // Post: Sends the entire hash table to os. For each index of the
    // hash table that contains a nonempty chain, outputs that index
    // followed by ": " followed by the chain.

    void toStream(ostream &os) const override {
        cerr << "HashTable::toStream: Exercise for the student." << endl;
        throw -1;
    }
};

#endif
