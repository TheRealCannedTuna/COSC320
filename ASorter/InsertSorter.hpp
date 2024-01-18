// File ASorter/InsertSorter.hpp

#ifndef SmartInsertSorter_HPP_
#define SmartInsertSorter_HPP_

#include "ASorter.hpp"

template<class T>
class InsertSorter : public ASorter<T> {
protected:
    virtual void split(ASeq<T>&, int lo, int &mid, int hi) override;
    virtual void join(ASeq<T>&, int lo, int mid, int hi) override;
};

template<class T>
void InsertSorter<T>::split(ASeq<T> &, int, int &mid, int hi) {
// Post: mid == hi.
    mid = hi;
}

template<class T>
void InsertSorter<T>::join(ASeq<T> &a, int lo, int mid, int hi) {
// Pre: mid == hi && sorted(a[lo..hi - 1]).
// Post: sorted(a[lo..hi]).
//    cerr << "InsertSorter<T>::join: Exercise for the student." << endl;
//    throw -1;
    // precondition check. boooooooooooooooooooring
    if (mid != hi) {
        cerr << "InsertSorter::join() mid == " << mid << "not equal to hi == " << hi << endl;
        throw -1;
    }

    // my code
//    T key = a[hi];
//    while (mid > lo && a[mid - 1] > key) {
//        // swap a[mid] and a[mid-1]
//        T temp = a[mid];
//        a[mid] = a[mid - 1];
//        a[mid - 1] = temp;
//        mid--;
//    }

    // warford's code

    int j = mid;
    T key = a[mid];
    while (lo < j && key < a[j - 1]) {
        a[j] = a[j - 1];
        j--;
    }
    a[j] = key;


    // for debugging, postcondition check
//    for(int i = lo; i < hi; ++i) {
//        if (a[i] > a[i+1]) {
//            cerr << "Postcondition sorted(a[lo..hi]) violated. You're a moron." << endl;
//            throw -1;
//        }
//    }
}

#endif
