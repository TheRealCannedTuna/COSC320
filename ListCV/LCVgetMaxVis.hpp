// File: ListCV/LCVgetMaxVis.hpp

#ifndef LCVgetMaxVis_hpp
#define LCVgetMaxVis_hpp

#include "ListCV.hpp"
using namespace std;

/**
 * Calls a helper that accumulates the max of the list,
 * as it traverses down the list.
 */
template<class T>
class LCVgetMaxVis : public AListCVVis<T> {
    // Pre: This list is not empty.
    // Post: The maximum element of this list is returned.
private:
    T _result; // Output result.

public:
    LCVgetMaxVis() = default;

    LCVgetMaxVis(const LCVgetMaxVis &rhs) = delete;             // Disabled.
    LCVgetMaxVis &operator=(const LCVgetMaxVis &rhs) = delete;  // Disabled.

    void visitMTList(AListCV<T> const &mtl) override;
    void visitNEList(AListCV<T> const  &nel) override;

    T result() const;
};

/**
 * Helper class doing forward accumulation to compute the max of the list.
 */
template<class T>
class LCVgetMaxVisHelp : public AListCVVis<T> {
private:
    int _result;
    int _acc;  // accumulated max.

public:
    LCVgetMaxVisHelp(int acc);
    void visitMTList(AListCV<T> const &mtl) override;
    void visitNEList(AListCV<T> const  &nel) override;
    [[nodiscard]] int result() const;
};

template<class T>
LCVgetMaxVisHelp<T>::LCVgetMaxVisHelp(int acc) : _acc(acc) {}

// ========= visit =========
template<class T>
void LCVgetMaxVis<T>::visitMTList(const AListCV<T> &) {
    assert(false);
}

template<class T>
void LCVgetMaxVis<T>::visitNEList(const AListCV<T> &nel) {
    auto &neHost = static_cast<const NEListCV<T>&>(nel); // auto in lieu of const NEListCV<T>.
    LCVgetMaxVisHelp<T> gMh(neHost.first());
    neHost.rest()->accept(gMh);
    _result = gMh.result();
}

template<class T>
void LCVgetMaxVisHelp<T>::visitMTList(const AListCV<T> &mtl) {
    _result = _acc;
}

template<class T>
void LCVgetMaxVisHelp<T>::visitNEList(const AListCV<T> &nel) {
    auto &neHost = static_cast<const NEListCV<T>&>(nel); // auto in lieu of const NEListCV<T>.
    if (neHost.first() > _acc) _acc = neHost.first();
    neHost.rest()->accept(*this);
}

// ========= result =========
template<class T>
T LCVgetMaxVis<T>::result() const {
    return _result;
}

template<class T>
int LCVgetMaxVisHelp<T>::result() const {
    return _result;
}

#endif
