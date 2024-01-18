// File: AStack/AStack.hpp

#ifndef AStack_HPP_
#define AStack_HPP_

#include <iostream> // ostream.

using namespace std;

/**
 * Represents the abstract LIFO (Last In First Out) behavior of a stack.
 *
 * @tparam T
 */
template<class T>
class AStack {
public:
    explicit AStack(int cap = 1) {};
    // Post: This stack is allocated with a capacity of cap
    // and initialized to be empty.

    virtual ~AStack() = default;

    virtual bool isEmpty() const = 0;
    // Post: true is returned if this stack is empty;
    // otherwise, false is returned.

    virtual bool isFull() const = 0;
    // Post: true is returned if this stack is full;
    // otherwise, false is returned.

    virtual T pop() = 0;
    // Pre: This stack is not empty.
    // Post: The top value in this stack is removed and returned.

    virtual void push(T const &val) = 0;
    // Pre: This stack is not full.
    // Post: val is stored on top of this stack.

    virtual T const &topOf() const = 0;
    // Pre: This stack is not empty.
    // Post: The top value from this stack is returned.

    virtual void toStream(ostream &os) const = 0;
    // Post: All the items on this stack from top to bottom
    // are written to os.
};

#endif
