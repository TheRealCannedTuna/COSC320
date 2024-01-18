// File: ListCV/LCVcontainsVis.hpp

#ifndef LCVcontainsVis_hpp
#define LCVcontainsVis_hpp

#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVcontainsVis : public AListCVVis<T> {
private:
    T _val;       // Input parameter.
    bool _result; // Output result.

public:
    LCVcontainsVis(T val);

    LCVcontainsVis(LCVcontainsVis const &rhs) = delete; // Disabled.
    LCVcontainsVis & operator=(LCVcontainsVis const &rhs) = delete;// Disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const  &host) override;

    bool result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if val is contained in this list; Otherwise, false is returned.
};

// ========= Constructor =========

template<class T>
LCVcontainsVis<T>::LCVcontainsVis(T val) : _val(val) {
}

// ========= visit =========

template<class T>
void LCVcontainsVis<T>::visitMTList(AListCV<T> const &) {
    _result = false;
}

template<class T>
void LCVcontainsVis<T>::visitNEList(AListCV<T>const &host) {
    const NEListCV<T> &neHost = static_cast<const NEListCV<T>&>(host);
    if (_val == neHost.first()) {
        _result = true;
    } else {
        neHost.rest()->accept(*this);
    }
}

// ========= result =========

template<class T>
bool LCVcontainsVis<T>::result() const {
    return _result;
}

#endif
