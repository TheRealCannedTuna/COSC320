// File: QueueV/QueueV.hpp

#ifndef SmartQueueV_HPP_
#define SmartQueueV_HPP_

#include "AQueue.hpp"
#include "VectorT.hpp"

// ========= QueueV =========
template<class T>
class QueueV: public AQueue<T> {
private:
    VectorT<T> _data;
    const int _cap;  // Queue capacity.

public:
    explicit QueueV(int cap = 1);
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
QueueV<T>::QueueV(int cap) :
    _cap(cap){
}


// ========= dequeue =========
template<class T>
T QueueV<T>::dequeue() {
    cerr << "dequeue: Exercise for the student." << endl;
    throw -1;
}

// ========= enqueue =========
template<class T>
void QueueV<T>::enqueue(T const &val) {
    cerr << "enqueue: Exercise for the student." << endl;
    throw -1;
}

// ========= headOf =========
template<class T>
T const &QueueV<T>::headOf() const {
    cerr << "headOf: Exercise for the student." << endl;
    throw -1;
}

// ========= isEmpty =========
template<class T>
bool QueueV<T>::isEmpty() const {
    cerr << "isEmpty: Exercise for the student." << endl;
    throw -1;
}

// ========= isFull =========
template<class T>
bool QueueV<T>::isFull() const {
    cerr << "isFull: Exercise for the student." << endl;
    throw -1;
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, QueueV<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void QueueV<T>::toStream(ostream &os) const {
    cerr << "toStream: Exercise for the student." << endl;
    throw -1;
}

#endif
