// File ASorter/MergeSorter.hpp

#ifndef SmartMergeSorter_HPP_
#define SmartMergeSorter_HPP_

#include "ASorter.hpp"
#include "ArrayT.hpp"

template<class T>
class MergeSorter : public ASorter<T> {

private:
    ArrayT<T> _tempA;

public:
    MergeSorter(int cap);

protected:
    virtual void split(ASeq<T> &a, int lo, int &mid, int hi) override;
    virtual void join(ASeq<T> &a, int lo, int mid, int hi) override;
};

template<class T>
MergeSorter<T>::MergeSorter(int cap) : _tempA(cap) {}

template<class T>
void MergeSorter<T>::split(ASeq<T> &, int lo, int &mid, int hi) {
// Post: mid ==(lo + hi + 1) / 2
    mid = (lo + hi + 1) / 2;
}
template<class T>
void MergeSorter<T>::join(ASeq<T> &a, int lo, int mid, int hi) {
    // cerr << "MergeSorter<T>::join: Exercise for the student." << endl;
    // throw -1;
    // precondition check. boring asf
    if (lo >= mid) {
        cerr << "Error: MergeSorter<T>::join(): lo == " << lo << " is not less than mid == " << mid << endl;
        throw -1;
    }
    if (lo >= hi) {
        cerr << "Error: MergeSorter<T>::join(): lo == " << lo << " is higher than hi == " << hi << endl;
        throw -1;
    }
    if (mid > hi) {
        cerr << "Error: MergeSorter<T>::join(): mid == " << mid << " is higher than hi == " << hi << endl;
        throw -1;
    }

    // my code

    // join to _tempA
    int i = lo;
    int j = mid;
    for (int k = lo; k <= hi; ++k) {
        if (j > hi && i < mid) {
            _tempA[k] = a[i++];
        } else if (i >= mid && j <= hi) {
            _tempA[k] = a[j++];
        } else if (a[i] < a[j]) {
            _tempA[k] = a[i++];
        } else {
            _tempA[k] = a[j++];
        }
    }
    // copy _tempA to &a
    for (int l = lo; l <= hi; ++l) {
        a[l] = _tempA[l];
    }

    // warford's code

//    int i = lo;
//    int j = mid;
//    for (int k = lo; k <= hi; k++) {
//        if (i >= mid) {
//            _tempA[k] = a[j++];
//        } else if (j > hi) {
//            _tempA[k] = a[i++];
//        } else if (a[i] < a[j]) {
//            _tempA[k] = a[i++];
//        } else {
//            _tempA[k] = a[j++];
//        }
//    }
//    for (int k = lo; k <= hi; k++) {
//        a[k] = _tempA[k];
//    }

    // error check, for debugging
//    for (int m = lo; m < hi; ++m) {
//        if(_tempA[m] > _tempA[m+1]) {
//            cerr << "You're a moron because " << _tempA[m] << " ain't less than " << _tempA[m+1] << " at index " << m
//                  << endl;
//            throw -1;
//        }
//    }
}

#endif
