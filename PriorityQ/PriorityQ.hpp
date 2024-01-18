// File: PriorityQ/PriorityQ.hpp

#ifndef PriorityQ_HPP_
#define PriorityQ_HPP_

#include "ArrayT.hpp"
#include "Heapifier.hpp"

// ========= PriorityQ =========
template<class T>
class PriorityQ {
private:
    ArrayT<T> _data;
    int _hiIndex;

public:
    PriorityQ(int cap);
    // Post: This priority queue is allocated with a capacity of cap
    // and initialized to be empty.

    T extractMax();
    // Pre: This priority queue is not empty.
    // Post: The maximum value in this priority queue is removed and returned.

    int heapSize() const;
    // Post: The size of this priority queue is returned.

    void increaseKey(int i, T const &key);
    // Pre: This priority queue is not empty, 0 <= i < heapSize(), and
    // key is at least as large as the key at index i.
    // Post: The value of the element at index i is increased to key.

    void insert(T const &val);
    // Pre: This priority queue is not full.
    // Post: val is stored in this priority queue.

    bool isEmpty() const;
    // Post: true is returned if this priority queue is full; otherwise, false is returned.

    bool isFull() const;
    // Post: true is returned if this priority queue is full; otherwise, false is returned.

    T const &maximum() const;
    // Pre: This priority queue is not empty.
    // Post: The maximum value from this priority queue is returned.

    void toStream(ostream &os) const;
    // Post: Each item on this priority queue prefixed with its index is written to os.
};

// ========= Constructor =========
template<class T>
PriorityQ<T>::PriorityQ(int cap) :
    _data(cap),
    _hiIndex(-1) {
}

// ========= extractMax =========
template<class T>
T PriorityQ<T>::extractMax() {
    if (isEmpty()) {
        cerr << "extractMax precondition violated: "
             << "Cannot extract maximum from an empty priority queue." << endl;
        throw -1;
    }
    cerr << "extractMax: Exercise for the student." << endl;
    throw -1;
}

// ========= heapSize =========
template<class T>
int PriorityQ<T>::heapSize() const {
    return _hiIndex + 1;
}

// ========= increaseKey =========
template<class T>
void PriorityQ<T>::increaseKey(int i, T const &key) {
    if (isEmpty()) {
        cerr << "increaseKey precondition violated: "
             << "Cannot increase key in an empty priority queue." << endl;
        throw -1;
    }
    if (i < 0 || _hiIndex < i) {
        cerr << "increaseKey precondition violated: "
             << "Index out of range. Index == " << i << endl;
        throw -1;
    }
    if (key < _data[i]) {
        cerr << "increaseKey precondition violated: "
             << "key must be at least as large as the key at intex i." << endl;
        throw -1;
    }
    cerr << "increaseKey: Exercise for the student." << endl;
    throw -1;
}

// ========= insert =========
template<class T>
void PriorityQ<T>::insert(T const &val) {
    if (isFull()) {
        cerr << "insert precondition violated: "
             << "Cannot insert into a full priority queue." << endl;
        throw -1;
    }
    _data[++_hiIndex] = val;
    siftUp(_data, 0, _hiIndex);
}

// ========= isEmpty =========
template<class T>
bool PriorityQ<T>::isEmpty() const {
    return _hiIndex == -1;
}

// ========= isFull =========
template<class T>
bool PriorityQ<T>::isFull() const {
    cerr << "isFull: Exercise for the student." << endl;
    throw -1;
}

// ========= maximum =========
template<class T>
T const &PriorityQ<T>::maximum() const {
    if (isEmpty()) {
        cerr << "maximum precondition violated: "
             << "An empty priority queue has no maximum." << endl;
        throw -1;
    }
    return _data[0];
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, PriorityQ<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void PriorityQ<T>::toStream(ostream &os) const {
    for (int i = 0; i <= _hiIndex; i++) {
        os << i << ":" << _data[i] << "  ";
    }
}

#endif
