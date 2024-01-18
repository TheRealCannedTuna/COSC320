// File: CAMetrics/CAMetrics.hpp

#ifndef CAMETRICS_HPP_
#define CAMETRICS_HPP_

#include <iostream> // istream, ostream.
#include "Counter.hpp"

using namespace std;

// ========= CAMetrics =========
/**
 * Wrapper class for data of type T using two static Counter objects:
 * one to keep track of the assignment count and one to keep track of the comparison count.
 * The assignment operator and the comparison operators are overloaded to update
 * the assignment count and the comparison count before they are applied to the data T.
 * This is in essence the decorator pattern.
 *
 * @tparam T data to compare or to assign.
 *
 */
template<class T>
class CAMetrics {
private:
    static Counter _compareCount;
    static Counter _assignCount;

    T _data;

public:
    CAMetrics(); // for array initialization.
    CAMetrics(CAMetrics const &rhs);
    T toT() const;
    void setT(const T &source);
    bool operator<(CAMetrics const &rhs);
    bool operator<(CAMetrics const &rhs) const;
    bool operator<=(CAMetrics const &rhs);
    bool operator<=(CAMetrics const &rhs) const;
    bool operator==(CAMetrics const &rhs);
    bool operator==(CAMetrics const &rhs) const;
    bool operator!=(CAMetrics const &rhs);
    bool operator!=(CAMetrics const &rhs) const;
    bool operator>=(CAMetrics const &rhs);
    bool operator>=(CAMetrics const &rhs) const;
    bool operator>(CAMetrics const &rhs);
    bool operator>(CAMetrics const &rhs) const;
    CAMetrics &operator=(CAMetrics const &rhs);

    static int getCompareCount();
    static int getAssignCount();
    static void clearCompareCount();
    static void clearAssignCount();
    static void setCost(int cost);

public:
    friend ostream &operator<<(ostream &os, CAMetrics<T> const &rhs) {
        os << rhs._data;
        return os;
    }

    friend istream &operator>>(istream &is, CAMetrics<T> &rhs) {
        rhs._assignCount.update();
        is >> rhs._data;
        return is;
    }
};

// ========= The static counters =========
template<class T>
Counter CAMetrics<T>::_compareCount;

template<class T>
Counter CAMetrics<T>::_assignCount;

// ========= Constructors =========
template<class T>
CAMetrics<T>::CAMetrics(void) {
}

template<class T>
CAMetrics<T>::CAMetrics(CAMetrics const &rhs) {
    _assignCount.update();
    _data = rhs._data;
}

// ========= toT =========
template<class T>
T CAMetrics<T>::toT() const {
    return _data;
}

// ========= setT =========
template<class T>
void CAMetrics<T>::setT(T const &source) {
    _assignCount.update();
    _data = source;
}

// ========= Comparison operators =========
template<class T>
bool CAMetrics<T>::operator<(CAMetrics<T> const &rhs) {
    _compareCount.update();
    return _data < rhs._data;
}

template<class T>
bool CAMetrics<T>::operator<(CAMetrics<T> const &rhs) const {
    _compareCount.update();
    return _data < rhs._data;
}

template<class T>
bool CAMetrics<T>::operator<=(CAMetrics<T> const &rhs) {
    _compareCount.update();
    return _data <= rhs._data;
}

template<class T>
bool CAMetrics<T>::operator<=(CAMetrics<T> const &rhs) const {
    _compareCount.update();
    return _data <= rhs._data;
}

template<class T>
bool CAMetrics<T>::operator==(CAMetrics<T> const &rhs) {
    _compareCount.update();
    return _data == rhs._data;
}

template<class T>
bool CAMetrics<T>::operator==(CAMetrics<T> const &rhs) const {
    _compareCount.update();
    return _data == rhs._data;
}

template<class T>
bool CAMetrics<T>::operator!=(CAMetrics<T> const &rhs) {
    _compareCount.update();
    return _data != rhs._data;
}

template<class T>
bool CAMetrics<T>::operator!=(CAMetrics<T> const &rhs) const {
    _compareCount.update();
    return _data != rhs._data;
}

template<class T>
bool CAMetrics<T>::operator>(CAMetrics<T> const &rhs) {
    _compareCount.update();
    return _data > rhs._data;
}

template<class T>
bool CAMetrics<T>::operator>(CAMetrics<T> const &rhs) const {
    _compareCount.update();
    return _data > rhs._data;
}

template<class T>
bool CAMetrics<T>::operator>=(CAMetrics<T> const &rhs) {
    _compareCount.update();
    return _data >= rhs._data;
}

template<class T>
bool CAMetrics<T>::operator>=(CAMetrics<T> const &rhs) const {
    _compareCount.update();
    return _data >= rhs._data;
}

// ========= operator= =========
template<class T>
CAMetrics<T> &CAMetrics<T>::operator=(CAMetrics<T> const &rhs) {
    _assignCount.update();
    if (_data != rhs._data ) {
        _data = rhs._data;
    }
    return *this;
}

// ========= Access methods =========
template<class T>
int  CAMetrics<T>::getCompareCount() {
    return _compareCount.getCount();
}

template<class T>
int  CAMetrics<T>::getAssignCount() {
    return _assignCount.getCount();
}

// ========= Clear methods =========
template<class T>
void  CAMetrics<T>::clearCompareCount() {
    _compareCount.clear();
}

template<class T>
void CAMetrics<T>::clearAssignCount() {
    _assignCount.clear();
}

// ========= setCost =========
template<class T>
void CAMetrics<T>::setCost(int cost) {
    _compareCount.setDelta(cost);
}

#endif
