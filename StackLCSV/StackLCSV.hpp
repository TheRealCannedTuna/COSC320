// File: StackLCSV/StackLCSV.hpp

#ifndef StackLCSV_HPP_
#define StackLCSV_HPP_

#include <iostream> // ostream.

#include "AStack.hpp"
#include "ListCSV.hpp"
#include "LCSVlengthVis.hpp"
#include "LCSVisEmptyVis.hpp"
#include "LCSVtoStreamVis.hpp"

using namespace std;

// ========= StackLCSV =========
template<class T>
class StackLCSV: public AStack<T> {
private:
    ListCSV<T> _listCSV;
    const int _cap;  // stack capacity.

public:
    explicit StackLCSV(int cap = 1);
    // This stack is initialized to be empty.

    bool isEmpty() const override;
    // Post: true is returned if this stack contains no element; otherwise, false is returned.

    bool isFull() const override;
    // Post: true is returned if the number of elements in this stack is equal to its cap;
    // otherwise, false is returned.

    T pop() override;
    // Pre: This stack is not empty.
    // Post: The top value in this stack is removed and returned.

    void push(T const &val) override;
    // Post: val is stored on top of this stack.

    T const &topOf() const override;
    // Pre: This stack is not empty.
    // Post: The top value from this stack is returned.

    void toStream(ostream &os) const override;
    // Post: All the items on this stack from top to bottom are written to os.
};

// ========= Constructor =========
template<class T>
StackLCSV<T>::StackLCSV(int cap): _cap(cap) {}

// ========= isEmpty =========
template<class T>
bool StackLCSV<T>::isEmpty() const {
    return length(_listCSV) == 0;
}

// ========= isFull =========
template<class T>
bool StackLCSV<T>::isFull() const {
    return length(_listCSV) == _cap;
}

// ========= pop =========
template<class T>
T StackLCSV<T>::pop() {
    cerr << "StackLCSV<T>::pop: Exercise for the student." << endl;
    // Don't forget the precondition.
    throw -1;
}

// ========= push =========
template<class T>
void StackLCSV<T>::push(const T &val) {
    cerr << "push: Exercise for the student." << endl;
    throw -1;
}

// ========= topOf =========
template<class T>
T const &StackLCSV<T>::topOf() const {
    cerr << "StackLCSV<T>::topOf: Exercise for the student." << endl;
    // Don't forget the precondition.
    throw -1;
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, StackLCSV<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void StackLCSV<T>::toStream(ostream &os) const {
    os << _listCSV;
}

#endif
