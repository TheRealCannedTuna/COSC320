// File: QueueLCSV/QueueLCSV.hpp

#ifndef QueueLCSV_HPP_
#define QueueLCSV_HPP_

#include "AQueue.hpp"
#include "ListCSV.hpp"
#include "LCSVappendVis.hpp"
#include "LCSVtoStreamVis.hpp"

// ========= QueueLCSV =========
template<class T>
class QueueLCSV: public AQueue<T> {
private:
    ListCSV<T> _listCSV;
    int _length; // length of _listCSV.
    const int _cap;  // Queue capacity.

public:
    QueueLCSV(int cap = 1);
    // Post: This queue is allocated with a capacity of cap
    // and initialized to be empty.

    T dequeue() override;
    // Pre: This queue is not empty.
    // Post: The head value in this queue is removed and returned.

    void enqueue(T const &val) override;
    // Pre: This queue is not full.
    // Post: val is stored at the tail of this queue.

    T const &headOf() const override;
    // Pre: This queue is not empty.
    // Post: The head value from this queue is returned.

    bool isEmpty() const override;
    // Post: true is returned if this queue is empty; otherwise, false is returned.

    bool isFull() const override;

    void toStream(ostream &os) const override;
    // Post: All the items on this queue from tail to head are written to os.
};

// ========= Constructor =========
template<class T>
QueueLCSV<T>::QueueLCSV(int cap) : _length(0), _cap(cap) {}

// ========= dequeue =========
template<class T>
T QueueLCSV<T>::dequeue() {
    cerr << "dequeue: Exercise for the student." << endl;
    throw -1;
}

// ========= enqueue =========
template<class T>
void QueueLCSV<T>::enqueue(T const &val) {
    cerr << "enqueue: Exercise for the student." << endl;
    throw -1;
}

// ========= headOf =========
template<class T>
T const &QueueLCSV<T>::headOf() const {
    cerr << "headOf: Exercise for the student." << endl;
    throw -1;
}

// ========= isEmpty =========
template<class T>
bool QueueLCSV<T>::isEmpty() const {
    cerr << "isEmpty: Exercise for the student." << endl;
    throw -1;
}

// ========= isFull =========
template<class T>
bool QueueLCSV<T>::isFull() const {
    cerr << "isFull: Exercise for the student." << endl;
    throw -1;
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, QueueLCSV<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void QueueLCSV<T>::toStream(ostream &os) const {
    cerr << "toStream: Exercise for the student." << endl;
    throw -1;
}

#endif
