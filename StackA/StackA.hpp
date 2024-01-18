// File: StackA/StackA.hpp

#ifndef StackA_HPP_
#define StackA_HPP_

#include "AStack.hpp"
#include "ArrayT.hpp"

// ========= StackA =========
template<class T>
class StackA : public AStack<T> {
private:
    ArrayT<T> _data;
    int _top;

public:
    explicit StackA(int cap = 1);
    bool isEmpty() const override;
    bool isFull() const override;
    T pop() override;
    void push(T const &val) override;
    T const &topOf() const override;
    void toStream(ostream &os) const override;
};

// ========= Constructor =========
template<class T>
StackA<T>::StackA(int cap):
    _data(cap),
    _top(-1) {
}

// ========= isEmpty =========
template<class T>
bool StackA<T>::isEmpty() const {
    return _top == -1;
}

// ========= isFull =========
template<class T>
bool StackA<T>::isFull() const {
    return _top + 1 == _data.cap();
}

// ========= pop =========
template<class T>
T StackA<T>::pop() {
    if (isEmpty()) {
        cerr << "pop precondition violated: Cannot pop from an empty stack." << endl;
        throw -1;
    }
    return _data[_top--];
}

// ========= push =========
template<class T>
void StackA<T>::push(T const &val) {
    _top++;
    _data[_top] = val;
}

// ========= topOf =========
template<class T>
T const &StackA<T>::topOf() const {
    if (isEmpty()) {
        cerr << "topOf precondition violated: An empty stack has no top." << endl;
        throw -1;
    }
    return _data[_top];
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, StackA<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= toStream =========
template<class T>
void StackA<T>::toStream(ostream &os) const {
    os << "(";
    for (int i = _top; i > 0; i--) {
        os << _data[i] << ", ";
    }
    if (_top == -1) {
        os << ")";
    }
    else {
        os << _data[0] << ")";
    }
}

#endif
