// File: StackV/StackV.hpp

#ifndef StackV_HPP_
#define StackV_HPP_

#include "AStack.hpp"
#include "VectorT.hpp"

// ========= StackV =========
template<class T>
class StackV: public AStack<T> {
private:
    VectorT<T> _data;
    const int _cap; // Stack capacity (not the same as Vector _data capacity.

public:
    explicit StackV(int cap = 1);
    // Post: This stack is allocated with a capacity of cap
    // and initialized to be empty.

    bool isEmpty() const override;
    // Post: true is returned if this stack is empty; otherwise, false is returned.

    bool isFull() const override;
    // Post: true is returned if this stack is full; otherwise, false is returned.

    T pop() override;
    // Pre: This stack is not empty.
    // Post: The top value in this stack is removed and returned.

    void push(T const &val) override;
    // Pre: This stack is not full.
    // Post: val is stored on top of this stack.

    T const &topOf() const override;
    // Pre: This stack is not empty.
    // Post: The top value from this stack is returned.

    void toStream(ostream &os) const override;
    // Post: All the items on this stack from top to bottom are written to os.
};

// ========= Constructor =========
template<class T>
StackV<T>::StackV(int cap):
    _cap(cap){
}

// ========= isEmpty =========
template<class T>
bool StackV<T>::isEmpty() const {
    cerr << "isEmpty: Exercise for the student." << endl;
    throw -1;
}

// ========= isFull =========
template<class T>
bool StackV<T>::isFull() const {
    cerr << "isFull: Exercise for the student." << endl;
    throw -1;
}

// ========= pop =========
template<class T>
T StackV<T>::pop() {
    if (isEmpty()) {
        cerr << "pop precondition violated: Cannot pop from an empty stack." << endl;
        throw -1;
    }
    cerr << "pop: Exercise for the student." << endl;
    throw -1;
}

// ========= push =========
template<class T>
void StackV<T>::push(T const &val) {
    cerr << "push: Exercise for the student." << endl;
    throw -1;
}

// ========= topOf =========
template<class T>
T const &StackV<T>::topOf() const {
    if (isEmpty()) {
        cerr << "topOf precondition violated: An empty stack has no top." << endl;
        throw -1;
    }
    cerr << "topOf: Exercise for the student." << endl;
    throw -1;
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, StackV<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void StackV<T>::toStream(ostream &os) const {
    cerr << "toStream: Exercise for the student." << endl;
    throw -1;
}

#endif // SmartStackV_HPP_
