// File: StackL/StackL.hpp

#ifndef StackL_HPP_
#define StackL_HPP_

#include <iostream> // ostream.

#include "AStack.hpp"
#include "ListL.hpp"

using namespace std;

// ========= StackL =========
template<class T>
class StackL : public AStack<T> {
private:
    ListL<T> _listL;
    const int _cap;  // Stack capacity.

public:
    StackL(int cap = 1);
    bool isEmpty() const override;
    bool isFull() const override;
    T pop() override;
    void push(T const &val) override;
    T const &topOf() const override;
    void toStream(ostream &os) const override;
};

// ========= Constructor =========
template<class T>
StackL<T>::StackL(int cap):
    _listL(),
    _cap(cap) {
}


// ========= isEmpty =========
template<class T>
bool StackL<T>::isEmpty() const {
    return _listL.isEmpty();
}

// ========= isFull =========
template<class T>
bool StackL<T>::isFull() const {
    return _listL.length() == _cap;
}

// ========= pop =========
template<class T>
T StackL<T>::pop() {
    if (isEmpty()) {
        cerr << "pop: cannot pop an empty stack" << endl;
        throw -1;
    }
    return _listL.remFirst();
}

// ========= push =========
template<class T>
void StackL<T>::push(const T &val) {
    if (isFull()) {
        cerr << "push precondition violated: Cannot push onto a full stack." << endl;
        throw -1;
    }
    _listL.prepend(val);
}

// ========= topOf =========
template<class T>
T const &StackL<T>::topOf() const {
    if (isEmpty()) {
        cerr << "topOf: stack is empty lmao" << endl;
        throw -1;
    }
    return _listL.first();
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, StackL<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void StackL<T>::toStream(ostream &os) const {
    _listL.toStream(os);
}

#endif
