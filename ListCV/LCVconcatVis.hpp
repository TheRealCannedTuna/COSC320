// File: ListCV/LCVconcatVis.hpp

#ifndef LCVconcatVis_hpp
#define LCVconcatVis_hpp

#include "ListCV.hpp"
#include "LCVcloneVis.hpp"
using namespace std;

template<class T>
class LCVconcatVis : public AListCVVis<T> {
private:
    shared_ptr<const AListCV<T>> _suffix; // Input parameter.
    shared_ptr<AListCV<T>> _result; // Output result.

public:
    explicit LCVconcatVis(shared_ptr<const AListCV<T>> suffix);

    LCVconcatVis(LCVconcatVis const &rhs) = delete;            // disabled.
    LCVconcatVis &operator=(LCVconcatVis const &rhs) = delete; // disabled.

    void visitMTList(AListCV<T> const &host) override;
    void visitNEList(AListCV<T> const &host) override;

    shared_ptr<AListCV<T>>  result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list with suffix appended is returned.
};

// ========= Constructor =========
template<class T>
LCVconcatVis<T>::LCVconcatVis(shared_ptr<const AListCV<T>> suffix): _suffix(suffix) {}

// ========= visit =========
template<class T>
void LCVconcatVis<T>::visitMTList(AListCV<T> const &) {
    LCVcloneVis<T> cloneVis;
    _suffix->accept(cloneVis);
    _result = cloneVis.result();
}

template<class T>
void LCVconcatVis<T>::visitNEList(AListCV<T> const &host) {
    const NEListCV<T> &neHost = static_cast<const NEListCV<T>&>(host);
    neHost.rest()->accept(*this);
    _result = make_shared<NEListCV<T>>(neHost.first(), _result);
}

// ========= result =========
template<class T>
shared_ptr<AListCV<T>>  LCVconcatVis<T>::result() const {
    return _result;
}

#endif
