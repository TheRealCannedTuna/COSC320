// File: ListCV/LCVlengthVis.hpp

#ifndef LCVlengthVis_hpp
#define LCVlengthVis_hpp

#include <iostream>
using namespace std;

#include "ListCV.hpp"

template<class T>
class LCVlengthVis : public AListCVVis<T> {
private:
    int _result; // Output result.

private:

public:
    LCVlengthVis() = default;

    LCVlengthVis(const LCVlengthVis &rhs) = delete; // Disabled.
    LCVlengthVis &operator=(const LCVlengthVis &rhs) = delete; // Disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const  &host) override;
    [[nodiscard]] int result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: The length of the host list is returned.
};

// ========= visit =========
template<class T>
void LCVlengthVis<T>::visitMTList(const AListCV<T> &) {
    _result = 0;
}

template<class T>
void LCVlengthVis<T>::visitNEList(const AListCV<T> &host) {
    host.rest()->accept(*this);
    _result = 1 + _result;
}

// ========= result =========
template<class T>
int LCVlengthVis<T>::result() const {
    return _result;
}

#endif
