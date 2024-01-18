//
// Created by Dung Nguyen on 8/3/21.
//

#ifndef DP4DSDISTRIBUTION_ListCVZ_HPP
#define DP4DSDISTRIBUTION_ListCVZ_HPP

#include <iostream> // ostream.
#include <cassert>
#include <memory>
using namespace std;

#include "AListCVZ.hpp"
#include "AListCVZVis.hpp"

// ========= The empty (MT) list =========
template<class T>
class MTListCVZ : public AListCVZ<T> {

public:
    MTListCVZ() = default;
    ~MTListCVZ() {
//        cout << "~MTListCVZ() called!" << endl;
    } // TODO remove

    T const &first() const override;
    shared_ptr<const AListCVZ<T>> rest() const override;
    shared_ptr<void> accept(AListCVZVis<T> &visitor) const override;

private:
    MTListCVZ(MTListCVZ<T> const &rhs); // Disabled.
    MTListCVZ &operator=(MTListCVZ<T> const &rhs); // Disabled.
};

// ========= The non-empty(NE) list =========
template<class T>
class NEListCVZ : public AListCVZ<T> {
private:
    T  _first;
    shared_ptr<const AListCVZ<T>> _rest;

private:
    NEListCVZ(NEListCVZ<T> const &rhs); // Disabled.
    NEListCVZ &operator=(NEListCVZ<T> const &rhs); // Disabled.

public:
    NEListCVZ(T first);
    // Post: This list exists and contains exactly one element, first.

    NEListCVZ(T first, shared_ptr<const AListCVZ<T>> rest); // pre: rest != nullptr
    // Post: This list exists and contains first and rest.

    ~NEListCVZ() {
//        cout << "~NEListCVZ() called!" << endl;
    } // TODO remove


    T const &first() const override;
    shared_ptr<const AListCVZ<T>> rest() const override;
    shared_ptr<void> accept(AListCVZVis<T> &visitor) const override;
};

// ========= Constructors =========
template<class T>
NEListCVZ<T>::NEListCVZ(T first):       _first(first) , _rest(new MTListCVZ<T>()){
//    _first = first;
//    _rest = make_shared<MTListCVZ<T>>();
}

template<class T>
NEListCVZ<T>::NEListCVZ(T first, shared_ptr<const AListCVZ<T>> rest) :  _first (first), _rest(rest) {
//    _first = first;
//    _rest = rest;
}

// ========= first and rest =========
template<class T>
T const &MTListCVZ<T>::first() const {
    assert(false);
}

template<class T>
shared_ptr<const AListCVZ<T>> MTListCVZ<T>::rest() const {
    assert(false);
}

template<class T>
T const &NEListCVZ<T>::first() const {
    return _first;
}

template<class T>
shared_ptr<const AListCVZ<T>> NEListCVZ<T>::rest() const {
    return _rest;
}

// ========= accept =========
template<class T>
shared_ptr<void> MTListCVZ<T>::accept(AListCVZVis<T> &visitor) const {
    return visitor.visitMTList(*this);
}

template<class T>
shared_ptr<void> NEListCVZ<T>::accept(AListCVZVis<T> &visitor) const {
    return visitor.visitNEList(*this);
}

#endif //DP4DSDISTRIBUTION_ListCVZ_HPP
