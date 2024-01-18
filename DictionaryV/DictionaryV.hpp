// File: DictionaryV/DictionaryV.hpp

#ifndef DICTIONARYV_HPP_
#define DICTIONARYV_HPP_

#include "ADictionary.hpp"
#include "VectorT.hpp"

// ========= DictionaryV =========

template <class K, class V>
class DictionaryV : public ADictionary<K, V> {
private:
    VectorT<shared_ptr<DictPair<K, V>>> _data;
    const int _cap; // Dictionary capacity (not the same as Vector _data capacity.
                    // Invariant: 0 <= _data._size() <= _cap.

public:

    DictionaryV(int cap = 1) :
        _cap(cap){
    }

    void clear() {
        int size = _data.size();
        while (size > 0) {
            _data.remove(--size);
        }
    }

    bool isFull() const {
        // Post: true is returned if this dictionary is full;
        // otherwise, false is returned.
        cerr << "isFull: Exercise for the student." << endl;
        throw -1;
    }

    void insert(K const &key, V const &val) {
        // Binary search for key in _data; if it's there, replace the corresponding old val with the new val.
        int lo  = 0;
        int hi  = _data.size() - 1;
        int mid;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (key < _data[mid]->key()) {
                hi = mid - 1;
            } else if (key > _data[mid]->key()) {
                lo = mid + 1;
            } else {  // key exists in _data
                cerr << "DictionaryV<K, V>::insert: Exercise for the student." << endl;
                throw -1;
            }
        }

        if (isFull()) {
            cerr << "insert precondition violated: " <<
                "Cannot insert into a full dictionary." << endl;
            throw -1;
        }

        // key is not in _data and dictionary is not full: find the correct index to insert (key,val).
        cerr << "DictionaryV<K, V>::insert: Exercise for the student." << endl;
        throw -1;
    }

    bool remove(K const &key, V &val) {
        cerr << "DictionaryV<K, V>::remove: Exercise for the student." << endl;
        throw -1;
    }

    bool contains(K const &key, V &val) const {
        int lo  = 0;
        int mid = 0;
        int hi  = _data.size() - 1;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (key < _data[mid]->key()) {
                hi = mid - 1;
            } else if (key > _data[mid]->key()) {
                lo = mid + 1;
            } else {
                val = _data[mid]->val();
                return true;
            }
        }
        return false;
    }

    void toStream(ostream &os) const {
        int size = _data.size();
        for (int i = 0; i < size; i++) {
            os << i << ": " << *(_data[i]) << endl;
        }
    }
};

#endif
