// File: SortProbe/ArrProbe.hpp

#ifndef ArrProbe_HPP
#define ArrProbe_HPP

#include <cassert>

#include "ASeq.hpp"
#include "ArrayT.hpp"
#include "Counter.hpp"

// ========= ArrProbe =========
/**
 * Decorator for Array<T> to count the number of times operator[] is called.
 *
 * @tparam T
 */
template<class T>
class ArrProbe : public ASeq<T> {
private:
    ArrayT<T>& _arrayT;
    Counter _probeCount;

public:
    ArrProbe(ArrayT<T>& arrayT);

    T &operator[](int i) override; // For read/write.
    T const &operator[](int i) const override; // For read-only.

    int cap() const override { return _arrayT.cap(); }
    
    void toStream(ostream &os) const override;
    // Pre: operator<< is defined for T.
    // Post: A string representation of this array is returned to output stream os.

    int fromStream(istream &is) override;
    // Pre: operator>> is defined for T.
    // Post: The items of input stream is are appended to this array.


    void clearProbeCount() { _probeCount.clear(); }

    int getProbeCount() const { return _probeCount.getCount(); }

    void setCost(int cost) { _probeCount.setDelta(cost); }
    
    ArrProbe(ArrProbe const &rhs) = delete; // Disabled.
    ArrProbe &operator=(ArrProbe const &rhs) = delete; // Disabled.
};

// ========= Constructor =========
template<class T>
ArrProbe<T>::ArrProbe(ArrayT<T>& arrayT) :
    _arrayT(arrayT),
    _probeCount(1) {
}

// ========= operator[] =========
template<class T>
T &ArrProbe<T>::operator[](int i) {
    _probeCount.update();
    return _arrayT[i];
}

template<class T>
T const &ArrProbe<T>::operator[](int i) const {
    return _arrayT[i];
}

// ========= toStream =========
template<class T>
void ArrProbe<T>::toStream(ostream &os) const {
    _arrayT.toStream(os);
}

// ========= fromStream =========
template<class T>
int ArrProbe<T>::fromStream(istream &is) {
    return _arrayT.fromStream(is);
}

#endif
