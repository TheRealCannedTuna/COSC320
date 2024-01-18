// File: QueueA/QueueA.hpp

#ifndef QueueA_HPP_
#define QueueA_HPP_

#include "AQueue.hpp"
#include "ArrayT.hpp"

// ========= QueueA =========
/**
 * A circular queue implemented as an array.
 * @tparam T
 */
template<class T>
class QueueA: public AQueue<T> {
private:
    ArrayT<T> _data;
    int _head, _tail;

public:
    explicit QueueA(int cap = 1);
    T dequeue() override;
    void enqueue(T const &val) override;
    T const &headOf() const override;
    bool isEmpty() const override;
    bool isFull() const override;
    void toStream(ostream &os) const override;
};

// ========= Constructor =========
template<class T>
QueueA<T>::QueueA(int cap) :
    _data(cap + 1),
    _head(0),
    _tail(0) {
}

// ========= dequeue =========
template<class T>
T QueueA<T>::dequeue() {
    if (isEmpty()) {
        cerr << "dequeue: queue is empty lmao" << endl;
        throw -1;
    }
    auto temp = _data[_head];
    _head = (_head + 1) % _data.cap();
    return temp;
}

// ========= enqueue =========
template<class T>
void QueueA<T>::enqueue(T const &val) {
    if (isFull()) {
        cerr << "enqueue: queue is full lmao" << endl;
        throw -1;
    }
    _data[_tail] = val;
    _tail = (_tail + 1) % _data.cap();
}

// ========= headOf =========
template<class T>
T const &QueueA<T>::headOf() const {
    if (isEmpty()) {
        cerr << "headOf: there is no head of an empty list lmao" << endl;
        throw -1;
    }
    return _data[_head];
}

// ========= isEmpty =========
template<class T>
bool QueueA<T>::isEmpty() const {
    return _head == _tail;
}

// ========= isFull =========
template<class T>
bool QueueA<T>::isFull() const {
    return _head == (_tail + 1) % _data.cap();
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, QueueA<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void QueueA<T>::toStream(ostream &os) const {
    for (int i = _head; i != _tail; i = (i + 1) % _data.cap()) {
        os << _data[i] << "  ";
    }
    os << endl;

}

#endif
