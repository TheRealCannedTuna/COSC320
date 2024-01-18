// File: ASeq/ASeq.hpp
// Abstract Sequence Template Class.

#ifndef ASEQ_HPP_
#define ASEQ_HPP_

#include <iostream> // istream, ostream.
#include <type_traits>
using namespace std;

/**
 * Type trait that determines if a type T is a shared_ptr or not.
 * ArrayT<T>::fromStream and VectorT<T>::fromstream illustrate its usage.
 *
 * @tparam T type to be tested.
 */
template<class T>
struct is_shared_ptr : false_type {}; // T is not a shared_ptr.
template<class T>
struct is_shared_ptr<shared_ptr<T>> : true_type {}; // T is a shared_ptr.

/**
 * Pure abstract class representing the mathematical notion of a
 * sequence, which is a function from the integers to a set of data
 * of type T indexed by integers.
 *
 * @tparam T the data element type.
 */
template<class T>
class ASeq {
public:
    explicit ASeq(int cap = 0) {}; // Avoid implicit conversion.
    virtual ~ASeq() = default;
    virtual T &operator[](int i) = 0; // For read/write.
    virtual T const &operator[](int i) const = 0; // For read-only.
    virtual int cap() const = 0;

    virtual void toStream(ostream &os) const = 0;
    // Pre: operator<< is defined for T.
    // Post: A string representation of this sequence is returned to output stream os.

    virtual int fromStream(istream &is) = 0;
    // Pre: operator>> is defined for T.
    //      If possible overload operator>> as needed.
    // Post: The items of input stream is are appended to this sequence.


    ASeq(ASeq const &rhs) = delete; // Disabled.
    ASeq &operator=(ASeq const &rhs) = delete; // Disabled.
};

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, ASeq<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= operator>> =========
template<class T>
istream &operator>>(istream &is, ASeq<T> &rhs) {
    rhs.fromStream(is);
    return is;
}

#endif
