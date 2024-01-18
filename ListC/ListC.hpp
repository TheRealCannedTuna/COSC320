// File: ListC/ListC.hpp

#ifndef LISTC_HPP_
#define LISTC_HPP_

#include <iostream> // ostream.
using namespace std;

#include "AListC.hpp"

// ========= The empty(MT) list =========
template<class T>
class MTListC :public AMTListC<T> {
public:
    MTListC() = default;

    MTListC(MTListC const &rhs) = delete; // Disabled.
    MTListC &operator=(MTListC const &rhs) = delete; // Disabled.

    shared_ptr<AListC<T>> clone() const override;
    shared_ptr<AListC<T>> prepend(T const &val) const override;
    shared_ptr<AListC<T>> append(T const &val) const override;
    shared_ptr<AListC<T>> concat(shared_ptr<const AListC<T>>  suffix) const override;

    shared_ptr<AListC<T>> reverse() const override;
    shared_ptr<AListC<T>> reverseHelper(shared_ptr<AListC<T>> accumReverse) const override;

    int length() const override;
    bool isEmpty() const override;
    bool contains(T val) const override;

    bool equals(AListC<T> const &rhs) const override;
    bool equalsHelper(T first, AListC<T> const &rest) const override;

    T const &max() const override;
    T const &maxHelper(T const &m) const override;

    shared_ptr<AListC<T>> remFirst() const override;

    shared_ptr<AListC<T>> remLast() const override;
    shared_ptr<AListC<T>> remLastHelper(T f) const override;

    shared_ptr<AListC<T>> remove(T val) const override;
    shared_ptr<AListC<T>> zip(shared_ptr<const AListC<T>>  other) const override;
    shared_ptr<AListC<T>> evenIndex() const override;
    shared_ptr<AListC<T>> oddIndex() const override;

    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;
};

// ========= The non-empty(NE) list =========
template<class T>
class NEListC :public ANEListC<T> {

private:
    T const _first;
    shared_ptr<const AListC<T>> _rest;

private:

public:
    NEListC(T const &first);
    // Post: This list exists and contains exactly one element, first.

    NEListC(T const &first, shared_ptr<const AListC<T>> rest);
    // Post: This list exists and contains first and rest.

    NEListC(NEListC const &rhs) = delete; // Disabled.
    NEListC &operator=(NEListC const &rhs) = delete; // Disabled.

    T const &first() const override;
    shared_ptr<const AListC<T>>  rest() const override;

    shared_ptr<AListC<T>> clone() const override;
    shared_ptr<AListC<T>> prepend(T const &val) const override;
    shared_ptr<AListC<T>> append(T const &val) const override;
    shared_ptr<AListC<T>> concat(shared_ptr<const AListC<T>> suffix) const override;

    shared_ptr<AListC<T>> reverse() const override;
    shared_ptr<AListC<T>> reverseHelper(shared_ptr<AListC<T>> accumReverse) const override;

    int length() const override;
    bool isEmpty() const override;
    bool contains(T val) const override;

    bool equals(AListC<T> const &rhs) const override;
    bool equalsHelper(T first, AListC<T> const &rest) const override;

    T const &max() const override;
    T const &maxHelper(T const &m) const override;

    shared_ptr<AListC<T>> remFirst() const override;

    shared_ptr<AListC<T>> remLast() const override;
    shared_ptr<AListC<T>> remLastHelper(T f) const override;

    shared_ptr<AListC<T>> remove(T val) const override;
    shared_ptr<AListC<T>> zip(shared_ptr<const AListC<T>>  other) const override;
    shared_ptr<AListC<T>> evenIndex() const override;
    shared_ptr<AListC<T>> oddIndex() const override;

    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;

};

// ========= Constructors =========
template<class T>
NEListC<T>::NEListC(T const &first) :_first(first), _rest(new MTListC<T>()) {}
template<class T>
NEListC<T>::NEListC(T const &first, shared_ptr<const AListC<T>> rest) :_first(first), _rest(rest) {}

// ========= first =========
template<class T>
T const &NEListC<T>::first() const {
    return _first;
}

// ========= rest =========
template<class T>
shared_ptr<const AListC<T>> NEListC<T>::rest() const {
    return _rest;
}

// ========= clone =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::clone() const {
    return make_shared<MTListC<T>>();
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::clone() const {
    return make_shared<NEListC<T>>(_first, _rest->clone());
}

// ========= prepend =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::prepend(T const &val) const {
    return make_shared<NEListC<T>>(val, this->shared_from_this());
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::prepend(T const &val) const {
    return make_shared<NEListC<T>>(val, this->shared_from_this());
}

// ========= append =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::append(T const &val) const {
    return make_shared<NEListC<T>>(val, this->clone());
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::append(T const &val) const {
    auto temp = _rest->append(val);
    auto result = make_shared< NEListC<T>>(_first, temp);
    return result;
}

// ========= concat =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::concat(shared_ptr<const AListC<T>>  suffix) const {
    cerr << "MTListC<T>::concat: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::concat(shared_ptr<const AListC<T>>  suffix) const {
    //  return new NEListC<T>(_first, _rest->concat(suffix)); would be a memory leak.
    cerr << "NEListC<T>::concat: Exercise for the student." << endl;
    throw -1;
}

// ========= reverse =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::reverse() const {
    return make_shared<MTListC<T>>();
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::reverse() const {
    auto accRev = make_shared<NEListC<T>>(_first);
    auto result = _rest->reverseHelper(accRev);
    return result;
}
template<class T>
shared_ptr<AListC<T>> MTListC<T>::reverseHelper(shared_ptr<AListC<T>> accumReverse) const {
    return accumReverse->clone();
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::reverseHelper(shared_ptr<AListC<T>> accumReverse) const {
    auto accRev = make_shared<NEListC<T>>(_first, accumReverse);
    auto result = _rest->reverseHelper(accRev);
    return result;
}

// ========= length =========
template<class T>
int MTListC<T>::length() const {
    cerr << "MTListC<T>::length: Exercise for the student." << endl;
    throw -1;
}
template<class T>
int NEListC<T>::length() const {
    cerr << "NEListC<T>::length: Exercise for the student." << endl;
    throw -1;
}

// ========= isEmpty =========
template<class T>
bool MTListC<T>::isEmpty() const {
    cerr << "MTListC<T>::isEmpty: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::isEmpty() const {
    cerr << "NEListC<T>::isEmpty: Exercise for the student." << endl;
    throw -1;
}

// ========= contains =========
template<class T>
bool MTListC<T>::contains(T val) const {
    cerr << "MTListC<T>::contains: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::contains(T val) const {
    cerr << "bool NEListC<T>::contains: Exercise for the student." << endl;
    throw -1;
}

// ========= equals =========
template<class T>
bool MTListC<T>::equals(AListC<T> const &rhs) const {
    cerr << "MTListC<T>::equals: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::equals(AListC<T> const &rhs) const {
    cerr << "NEListC<T>::equals: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool MTListC<T>::equalsHelper(T, AListC<T> const &) const {
    cerr << "MTListC<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::equalsHelper(T first, AListC<T> const &rest) const {
    cerr << "NEListC<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}

// ========= max =========
template<class T>
T const &MTListC<T>::max() const {
    cerr << "Precondition violated: An empty list has no maximum." << endl;
    throw -1;
}
template<class T>
T const &NEListC<T>::max() const {
    return _rest->maxHelper(_first);
}
template<class T>
T const &MTListC<T>::maxHelper(T const &m) const {
    return m;
}
template<class T>
T const &NEListC<T>::maxHelper(T const &m) const {
    return _first <= m ? _rest->maxHelper(m) : _rest->maxHelper(_first);
}

// ========= remFirst =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::remFirst() const {
    return make_shared<MTListC<T>>();
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::remFirst() const {
    return _rest->clone();
}

// ========= remLast =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::remLast() const {
    cerr << "MTListC<T>::remLast: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::remLast() const {
    cerr << "NEListC<T>::remLast: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> MTListC<T>::remLastHelper(T f) const {
    cerr << "MTListC<T>::remLastHelper: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::remLastHelper(T f) const {
    cerr << "NEListC<T>::remLastHelper: Exercise for the student." << endl;
    throw -1;
}

// ========= remove =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::remove(T val) const {
    cerr << "MTListC<T>::remove: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::remove(T val) const {
    cerr << "NEListC<T>::remove: Exercise for the student." << endl;
    throw -1;
}

// ========= zip =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::zip(shared_ptr<const AListC<T>>  other) const {
    cerr << "MTListC<T>::zip: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::zip(shared_ptr<const AListC<T>>  other) const {
    cerr << "NEListC<T>::zip: Exercise for the student." << endl;
    throw -1;
}

// ========= evenIndex =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::evenIndex() const {
    cerr << "MTListC<T>::evenIndex: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::evenIndex() const {
    cerr << "NEListC<T>::evenIndex: Exercise for the student." << endl;
    throw -1;
}

// ========= oddIndex =========
template<class T>
shared_ptr<AListC<T>> MTListC<T>::oddIndex() const {
    cerr << "MTListC<T>::oddIndex: Exercise for the student." << endl;
    throw -1;
}
template<class T>
shared_ptr<AListC<T>> NEListC<T>::oddIndex() const {
    cerr << "NEListC<T>::oddIndex: Exercise for the student." << endl;
    throw -1;
}

// ========= toStream =========
template<class T>
void MTListC<T>::toStream(ostream &os) const {
    os << "()";
}
template<class T>
void NEListC<T>::toStream(ostream &os) const {
    cerr << "NEListC<T>::toStream: Exercise for the student." << endl;
    throw -1;
}
template<class T>
void MTListC<T>::toStreamHelper(ostream &os) const {
    cerr << "MTListC<T>::toStreamHelper: Exercise for the student." << endl;
    throw -1;
}
template<class T>
void NEListC<T>::toStreamHelper(ostream &os) const {
    cerr << "NEListC<T>::toStreamHelper: Exercise for the student." << endl;
    throw -1;
}

#endif
