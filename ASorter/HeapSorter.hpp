// File ASorter/HeapSorter.hpp

#ifndef HeapSorter_HPP_
#define HeapSorter_HPP_

#include "ASorter.hpp"
#include "Heapifier.hpp" // siftDown.

template<class T>
class HeapSorter : public ASorter<T> {
public:
    HeapSorter(ASeq<T> &a, int lo, int hi);
    // Constructor initializes a to a heap.
    // Post: maxHeap(a[lo..hi]).

protected:
    virtual void split(ASeq<T> &a, int lo, int &mid, int hi) override;
    virtual void join(ASeq<T> &a, int lo, int mid, int hi) override;
};

template<class T>
HeapSorter<T>::HeapSorter(ASeq<T> &a, int lo, int hi) {
// Post: maxHeap(a[lo..hi]).
    for (int i = (lo + hi - 1) / 2; i >= lo; i--) {
        siftDown(a, lo, i, hi);
    }
}

template<class T>
void HeapSorter<T>::split(ASeq<T> &a, int lo, int &mid, int hi) {
// Pre: maxHeap(a[lo..hi]).
// Post: maxHeap(a[lo..hi - 1]).
// Post: a[hi] == old a[lo] && mid == hi.
    T temp = a[hi];
    a[hi] = a[lo];
    a[lo] = temp;
    siftDown(a, lo, lo, hi - 1);
    mid = hi;
}

template<class T>
void HeapSorter<T>::join(ASeq<T>&, int lo, int mid, int hi) {
}

#endif
