// File: ASorter/Heapifier.hpp

#ifndef Heapifier_HPP_
#define Heapifier_HPP_

#include "ASeq.hpp"

// ========= siftUp =========
template<class T>
void siftUp(ASeq<T> &a, int lo, int i) {
// Pre: maxHeap(a[lo..i - 1]).
// Post: maxHeap(a[lo..i]).
    T temp = a[i];
    int base = i;
    int parent = (i + lo - 1) / 2;
    while (lo < i && a[parent] < temp) {
        // swap temp and a[parent]
        T temp2 = temp;
        temp = a[parent];
        a[parent] = temp2;
        // i and parent climbs
        i = parent;
        parent = (i + lo - 1) / 2;
    }
    a[base] = temp;
}

// ========= siftDown =========
template<class T>
void siftDown(ASeq<T> &a, int lo, int i, int hi) {
// Pre: maxHeap(a[i + 1..hi]).
// Pre: lo <= i <= hi.
// Post: maxHeap(a[i..hi]).

// Original recursive method

//    int child = 2 * i - lo + 1; // Index of left child.
//    if (child <= hi) {
//        if (child < hi && a[child] < a[child + 1]) {
//            child++;
//        } // child is the index of the larger of the two children.
//        while (a[i] < a[child]) {
//            T temp = a[i];
//            a[i] = a[child];
//            a[child] = temp;
//            siftDown(a, lo, child, hi);
//        }
//    }

// my """"better"""" method

    int child = 2 * i - lo + 1;
    T key = a[i];
    int temp = i;
    if (child <= hi) {
        if (child < hi && a[child] < a[child + 1]) {
            child++;
        } // child is the index of the larger of the two children.
    }
    bool done = hi < child || key >= a[child];
    while (!done) {
        a[temp] = a[child];
        temp = child;

        child = 2 * temp - lo + 1;
        if (child <= hi) {
            if (child < hi && a[child] < a[child + 1]) {
                child++;
            } // child is the index of the larger of the two children.
        }
        done = hi < child || key >= a[child];   // no more children or children that are smaller
    }
    a[temp] = key;

//    siftUp(a, lo, temp);

    // warford's code
//
//    T temp = a[i];
//    int child = 2 * i - lo + 1; // Index of left child.
//    bool done = hi < child;
//    while (!done) {
//        if (child < hi && a[child] < a[child + 1]) {
//            child++;
//        }  // child is the index of the larger of the two children.
//        if (temp < a[child]) {
//            a[i] = a[child];
//            i = child;
//            child = 2 * i - lo + 1;
//            done = hi < child;
//        }
//        else {  // a[child] <= temp.
//            done = true;
//        }
//    }
//    a[i] = temp;


// garbage code, kept around as a relic of just how unsmart i am

    // find the place to go
//    int temp = i;
//    int child = 2 * i - lo + 1; // Index of left child.
//    if (child <= hi) {
//        if (child < hi && a[child] < a[child + 1]) {
//            child++;
//        } // child is the index of the larger of the two children.
//    }
//    bool done = hi < child;
//    while (!done) {
//        // temp goes down the tree (increases value)
//        temp = child;
//        child = 2 * temp - lo + 1; // Index of left child of temp.
//        if (child <= hi) {
//            if (child < hi && a[child] < a[child + 1]) {
//                child++;
//            } // child is the index of the larger of the two children.
//        }
//        done = hi < child || a[i] > a[child];
//    }
//    siftUp(a, lo, temp);
}

#endif
