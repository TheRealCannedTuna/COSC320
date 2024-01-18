// File: ListCV/LCVreverseVis.hpp

#ifndef LCVreverseVis_hpp
#define LCVreverseVis_hpp

#include "ListCV.hpp"
#include "LCVappendVis.hpp" // Using another plugin.
using namespace std;

// ========= reverse helper =========
template<class T>
class LCVreverseVisHelper : public AListCVVis<T> {
private:
    shared_ptr<AListCV<T>> _accumReverse; // Accumulated result.
    shared_ptr<AListCV<T>> _result; // Output result.

public:
    explicit LCVreverseVisHelper(shared_ptr<AListCV<T>> accumReverse);

    LCVreverseVisHelper(const LCVreverseVisHelper &rhs) = delete;               // Disabled.
    LCVreverseVisHelper &operator=(const LCVreverseVisHelper &rhs) = delete;    // Disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const  &host) override;

    shared_ptr<AListCV<T>> result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list reversed is returned.
};

// ========= Constructor =========
template<class T>
LCVreverseVisHelper<T>::LCVreverseVisHelper(shared_ptr<AListCV<T>> accumReverse): _accumReverse(accumReverse) {}

// ========= visit =========
template<class T>
void LCVreverseVisHelper<T>::visitMTList(const AListCV<T> &) {
    _result = _accumReverse;
}

template<class T>
void LCVreverseVisHelper<T>::visitNEList(const AListCV<T> &host) {
    auto &neHost = static_cast<const NEListCV<T>&>(host);
    _accumReverse = make_shared<NEListCV<T>>(neHost.first(), _accumReverse);
    neHost.rest()->accept(*this);
}

// ========= result =========
template<class T>
shared_ptr<AListCV<T>> LCVreverseVisHelper<T>::result() const {
    return _result;
}

// ========= reverse master =========
template<class T>
class LCVreverseVis : public AListCVVis<T> {
private:
    shared_ptr<AListCV<T>> _result; // Output result.

public:
    LCVreverseVis() = default;

    LCVreverseVis(const LCVreverseVis &rhs) = delete;               // disabled.
    LCVreverseVis &operator=(const LCVreverseVis &rhs) = delete;    // disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const  &host) override;

    shared_ptr<AListCV<T>> result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list reversed is returned.
};

// ========= visit =========
template<class T>
void LCVreverseVis<T>::visitMTList(const AListCV<T>  &) {
    _result = make_shared<MTListCV<T>>();
}

template<class T>
void LCVreverseVis<T>::visitNEList(const AListCV<T> &host) {
    auto &neHost = static_cast<const NEListCV<T>&>(host);
    LCVreverseVisHelper<T> reverseHelperVis(make_shared<NEListCV<T>>(neHost.first()));
    neHost.rest()->accept(reverseHelperVis);
    _result = reverseHelperVis.result();
}

// ========= result =========
template<class T>
shared_ptr<AListCV<T>> LCVreverseVis<T>::result() const {
    return _result;
}

#endif
