// File: ArrayT/ArrayT.hpp

#ifndef ArrayT_hpp
#define ArrayT_hpp

#include <iostream> // istream, ostream.
#include <memory>   // use smart pointers.
#include "ASeq.hpp"

using namespace std;

// ========= ArrayT =========
/**
 * Wrapper for a unique_ptr pointing to an array of data elements of type T.
 * It behaves like a regular array with overloaded operator[].
 * It is safe by not allowing out-out-bound indices.
 * delete[] will be called on the array of data elements whenever this
 * wrapper object goes out of scope.
 */

template<class T>
class ArrayT : public ASeq<T> {
private:
    unique_ptr<T[]> _data;
    int _cap;

public:
    explicit ArrayT(int cap = 1);

    ArrayT(ArrayT const &rhs) = delete; // Disabled.
    ArrayT &operator=(ArrayT const &rhs) = delete; // Disabled.

    int cap() const override;

    T &operator[](int i) override; // For read/write.
    T const &operator[](int i) const override; // For read-only.

    void toStream(ostream &os) const override;
    // Pre: operator<< is defined for T.
    // Post: A string representation of this array is returned to output stream os.

    int fromStream(istream &is) override;
    // Pre: operator>> is defined for T.
    // Post: The items of input stream is are appended to this array.

};

// ========= Constructor =========
template<class T>
ArrayT<T>::ArrayT(int cap) {
    if (cap < 1) {
        cerr << "ArrayT constructor precondition 0 < cap violated." << endl;
        cerr << "cap == " << cap << endl;
        throw -1;
    }
    _data = make_unique<T[]>(cap);
    _cap = cap;
}

// ========= cap =========
template<class T>
int ArrayT<T>::cap() const {
    return _cap;
}

// ========= operator[] =========
template<class T>
T &ArrayT<T>::operator[](int i) {
    if (i < 0 || _cap <= i) {
        cerr << "ArrayT index out of bounds: index == " << i << endl;
        throw -1;
    }
    return _data[i];
}

template<class T>
T const &ArrayT<T>::operator[](int i) const {
    if (i < 0 || _cap <= i) {
        cerr << "ArrayT index out of bounds: index == " << i << endl;
        throw -1;
    }
    return _data[i];
}

// ========= writeStream =========
template<class T>
void writeFormatted(ostream &os, ArrayT<T> const &a, int len, int width, int precision, int numCols) {
    // Pre: << is defined for T.
    // Post: num values are output from a to os, numCols items per line,
    // where num == min(len, a.cap()).
    int cap = a.cap();
    for (int i = 0; i < len && i < cap; i++) {
        os.width(width);
        os.precision(precision);
        os.setf(ios::fixed | ios::showpoint);
        os << a[i];
        if (i % numCols == (numCols-1)) {
            os << endl;
        }
    }
    os << endl;
}

// ========= toStream =========
template<class T>
void ArrayT<T>::toStream(ostream &os) const {
    os << "(";
    for (int i = 0; i < _cap - 1; i++) {
        os << _data[i] << ", ";
    }
    os << _data[_cap - 1] << ")";
}

// ========= fromStream =========
template<class T>
int ArrayT<T>::fromStream(istream &is) {
    int len = 0;
    if constexpr(!is_shared_ptr<T>::value)
                    for (int i = 0; i < _cap && is >> _data[i]; i++) {
                        len++;
                    }
    return len;
}

#endif
