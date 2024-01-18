// File: ListCV/LCVremLastVis.hpp

#ifndef LCVremLastVis_hpp
#define LCVremLastVis_hpp

#include "ListCV.hpp"
using namespace std;  

// Exercise for the student.

// ========= Master visitor to remove the last element =========
template<class T>
class LCVremLastVis : public AListCVVis<T> {
    // Post: A pointer to a copy of this list with the last element removed
    // is returned. A copy of an empty list is returned if this list is empty.
private:
    shared_ptr<AListCV<T>> _result; // Output result.

public:
    LCVremLastVis() = default;

    LCVremLastVis(const LCVremLastVis &rhs) = delete; // Disabled.
    LCVremLastVis &operator=(const LCVremLastVis &rhs) = delete; // Disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const  &host) override;

    shared_ptr<AListCV<T>> result() const;
};

// ========= Helper visitor to remove the last element =========
template<class T>
class LCVremLastVisHelper : public AListCVVis<T> {
private:
    T _first;
    shared_ptr<AListCV<T>> _helperResult; // Output result.

public:
    explicit LCVremLastVisHelper(T first);

    LCVremLastVisHelper(const LCVremLastVisHelper &rhs) = delete; // Disabled.
    LCVremLastVisHelper &operator=(const LCVremLastVisHelper &rhs) = delete; // Disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const  &host) override;

    shared_ptr<AListCV<T>> result() const;
};


// ========= Constructor =========

template<class T>
LCVremLastVisHelper<T>::LCVremLastVisHelper(T first) : _first(first) {
}

// ========= visit =========

template<class T>
void LCVremLastVis<T>::visitMTList(const AListCV<T> &) {
    _result = make_shared<MTListCV<T>>();
}

template<class T>
void LCVremLastVis<T>::visitNEList(const AListCV<T> &host) {
    const NEListCV<T> &neHost = static_cast<const NEListCV<T>&>(host);
    T first = neHost.first();
    LCVremLastVisHelper<T> remLastHelperVis(first);
    neHost.rest()->accept(remLastHelperVis);
    _result = remLastHelperVis.result();
}

template<class T>
void LCVremLastVisHelper<T>::visitMTList(const AListCV<T> &) {
    _helperResult =  make_shared<MTListCV<T>>();
}

template<class T>
void LCVremLastVisHelper<T>::visitNEList(const AListCV<T> &host) {
    LCVremLastVis<T> remLastVis;
    host.accept(remLastVis);
    _helperResult = make_shared<NEListCV<T>>(_first, remLastVis.result());
}

// ========= result =========

template<class T>
shared_ptr<AListCV<T>> LCVremLastVis<T>::result() const {
    return _result;
}

template<class T>
shared_ptr<AListCV<T>> LCVremLastVisHelper<T>::result() const {
    return _helperResult;
}

#endif
