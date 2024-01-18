//
// Created by Dung Nguyen on 8/3/21.
//

#ifndef DP4DSDISTRIBUTION_LCVZZPREPENDVIS_HPP
#define DP4DSDISTRIBUTION_LCVZZPREPENDVIS_HPP

#include "AListCVZVis.hpp"
#include "ListCVZ.hpp"
using namespace std;

template<class T>
class LCVZprependVis : public AListCVZVis<T> {
private:
    T _val; // Input parameter.

private:
    LCVZprependVis(const LCVZprependVis &rhs); // disabled.
    LCVZprependVis &operator=(const LCVZprependVis &rhs); // disabled.

public:
    LCVZprependVis(T val);

    ~LCVZprependVis() {
//        cout << "~LCVZprendVis() called." << endl;
    } // TODO remove

    shared_ptr<void> visitMTList(AListCVZ<T> const &host) override;
    shared_ptr<void> visitNEList(AListCVZ<T> const  &host) override;
//    shared_ptr<AListCVZ<T>> result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list with val prepended is returned.
};

// ========= Constructor =========

template<class T>
LCVZprependVis<T>::LCVZprependVis(T val) : _val(val) {
}

// ========= visit =========

template<class T>
shared_ptr<void> LCVZprependVis<T>::visitMTList(AListCVZ<T> const  &host) {
    return make_shared<NEListCVZ<T>>(_val);
}

template<class T>
shared_ptr<void> LCVZprependVis<T>::visitNEList(AListCVZ<T> const  &host) {
    return make_shared<NEListCVZ<T>>(_val, host.shared_from_this());
}

#endif //DP4DSDISTRIBUTION_LCVZPREPENDVIS_HPP
