// File: ASorter/QuickSorter.hpp

#ifndef SmartQuickSorter_HPP_
#define SmartQuickSorter_HPP_

#include <random>
#include "ASorter.hpp"

template<class T>
class QuickSorter : public ASorter<T> {
protected:
    virtual void split(ASeq<T> &a, int lo, int &mid, int hi) override;
    virtual void join(ASeq<T> &a, int lo, int mid, int hi) override;

private:
    random_device rdev{};
    default_random_engine engine{rdev()};
};

template<class T>
void QuickSorter<T>::split(ASeq<T> &a, int lo, int &mid, int hi) {
// Post: a[lo..mid-1] <= a[mid..hi]
    T temp;
    if (hi - lo > 4) {
        int mdn; // Index of the estimate of the median value.
        uniform_int_distribution<int> distr(lo, hi);
        // Find the estimate of the median.
        int mdn1 = distr(engine);
        int mdn2 = distr(engine);
        int mdn3 = distr(engine);
        if ((a[mdn2] <= a[mdn1] && a[mdn1] <= a[mdn3])
            || (a[mdn3] <= a[mdn1] && a[mdn1] <= a[mdn2])) {
            mdn = mdn1; // a[mdn1] is the median
        } else if ((a[mdn1] <= a[mdn2] && a[mdn2] <= a[mdn3])
                   || (a[mdn3] <= a[mdn2] && a[mdn2] <= a[mdn1])) {
            mdn = mdn2; // a[mdn2] is the median
        } else {
            mdn = mdn3; // a[mdn3] is the median
        }
        // Swap the estimate of the median with a[hi].
        temp = a[mdn];
        a[mdn] = a[hi];
        a[hi] = temp;
    }
    // Now do the split.
    T key = a[hi];
    mid = lo;
    for (int j = lo; j <= hi; j++) {
        if (a[j] <= key) {
            temp = a[mid];
            a[mid] = a[j];
            a[j] = temp;
            mid++;
        }
    }
    mid = hi < mid ? hi : mid; // If a[hi] contains the maximum element.
}

template<class T>
void QuickSorter<T>::join(ASeq<T>&, int lo, int mid, int hi) {
}

#endif
