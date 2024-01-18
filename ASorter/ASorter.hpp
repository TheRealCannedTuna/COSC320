// File: ASorter/ASorter.hpp

#ifndef ASORTER_HPP_
#define ASORTER_HPP_

#include <iostream>
#include "ASeq.hpp"

using namespace std;

template<class T>
class ASorter {

public:
    void sort(ASeq<T> &a, int lo, int hi);
    // Pre: 0 <= lo && hi < a.cap().
    // Post: sorted(a[lo..hi]).

    virtual ~ASorter() = default;
    // Virtual destructor necessary for subclassing.

protected:
    virtual void split(ASeq<T> &a, int lo, int &mid, int hi) = 0;
    // Pre: lo < hi.
    // Post: lo < mid <= hi.

    virtual void join(ASeq<T> &a, int lo, int mid, int hi) = 0;
    // Pre: lo < mid <= hi.
    // Pre: sorted(a[lo..mid-1]) && sorted(a[mid..hi]).
    // Post: sorted(a[lo..hi]).
};
template<class T>
void ASorter<T>::sort(ASeq<T> &a, int lo, int hi) {
    if (lo < 0 || a.cap() <= hi) {
        cerr << "ASorter<T>::sort precondition failed." << endl;
        cerr << "lo == " << lo << " a.cap() == " << a.cap()
             << " hi == " << hi << endl;
        throw -1;
    }
    if (lo < hi) {
        int mid;
        split(a, lo, mid, hi);
        sort(a, lo, mid - 1);
        sort(a, mid, hi);
        join(a, lo, mid, hi);
    }
}

#endif
