// File: AQueue/AQueue.hpp

#ifndef AQUEUE_HPP_
#define AQUEUE_HPP_

#include <iostream> // ostream.

using namespace std;

/**
 * Represents the abstract FIFO (First in First Out) behavior of a queue.
 *
 * @tparam T data stored in this queue.
 */
template<class T>
class AQueue {
public:
    explicit AQueue(int cap = 1) {}
    // Post: This queue is allocated with a capacity of cap
    // and initialized to be empty.

    virtual ~AQueue() = default;

    virtual T dequeue() = 0;
    // Pre: This queue is not empty.
    // Post: The head value in this queue is removed and returned.

    virtual void enqueue(T const &val) = 0;
    // Pre: This queue is not full.
    // Post: val is stored at the tail of this queue.

    virtual T const &headOf() const = 0;
    // Pre: This queue is not empty.
    // Post: The head value from this queue is returned.

    virtual bool isEmpty() const = 0;
    // Post: true is returned if this queue is empty;
    // otherwise, false is returned.

    virtual bool isFull() const = 0;
    // Post: true is returned if this queue is full;
    // otherwise, false is returned.

    virtual void toStream(ostream &os) const = 0;
    // Post: All the items on this queue from tail to head
    // are written to os.
};

#endif
