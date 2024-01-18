// File: ListCS/ListCS.hpp

#ifndef LISTCS_HPP_
#define LISTCS_HPP_

#include <iostream> // ostream.
#include <memory>

using namespace std;

template<class T> class AcsNode; // Forward declaration.
template<class T> class NEcsNode; // Forward declaration.
template<class T> class MTcsNode; // Forward declaration.

// ========= ListCS =========
template<class T>
class ListCS {
    friend class NEcsNode<T>;
    friend class MTcsNode<T>;
private:
    shared_ptr<AcsNode<T>> _head;  // state of the list: empty or not empty.

    explicit ListCS(shared_ptr<AcsNode<T>> node);
    // Post: _head points to node with no allocation.

public: // Constructors
    ListCS();
    // Post: This list is initialized to be empty.

    ListCS(ListCS<T> const &rhs) = delete;
    // Copy constructor disabled.

public:
    void append(T const &data);
    // Post: data is appended to this list.

    void clear();
    // Post: This list is cleared to the empty list.

    void concat(ListCS<T> &suffix);
    // Post: suffix is appended to this list.
    // suffix is empty (cut concatenate, as opposed to copy concatenate).

    bool contains(T const &data) const;
    // Post: true is returned if data is contained in this list;
    // Otherwise, false is returned.

private:
    shared_ptr<AcsNode<T>> copyHead(ListCS<T> const &rhs);
    // Post: A deep copy of the head of rhs is returned.

public:
    bool equals(ListCS<T> const &rhs) const;
    // Post: true is returned if this list equals list rhs; Otherwise, false is returned.
    // Two lists are equal if they contain the same number of equal elements in the same order.

private:
    bool equalsHelper(T const &first, ListCS<T> const &rest) const;
    // Post: true is returned if first equals this->first() and rest equals this->rest();
    // Otherwise, false is returned.

public:
    T &first();
    T const &first() const;
    // Pre: This list is not empty.
    // Post: A reference to the first element of this list is returned.

    bool isEmpty() const;
    // Post: true is returned if this list is empty; otherwise, false is returned.

    int length() const;
    // Post: The length of this list is returned.

    T const &max() const;
    // Pre: This list is not empty. T is totally ordered by operator>
    // Post: The maximum element of this list is returned.
private:
    T const &maxHelper(T const &val) const;
    // Post: The maximum element of this list and val is returned.

public:
    ListCS &operator=(ListCS<T> const &rhs);
    // Post: A deep copy of rhs is returned.

    void prepend(T const &data);
    // Post: data is prepended to this list.

    T remFirst();
    // Pre: This list is not empty.
    // Post: The first element is removed from this list and returned.

    T remLast();
    // Pre: This list is not empty.
    // Post: The last element is removed from this list and returned.

private:
    T remLastHelper(ListCS<T> &previous);
    // Pre: previous.rest() is this list.
    // Post: The last element of previous is removed and returned.

public:
    void remove(T const &data);
    // Post: If data is in this list, it is removed; Otherwise this list is unchanged.

    shared_ptr<ListCS<T>> rest();
    shared_ptr<ListCS<T>> const rest() const;
    // Pre: This list is not empty.
    // Post: A shared_ptr to the rest of this list is returned.

    void reverse();
    // Post: This list is reversed.

private:
    void reverseHelper(ListCS<T> &revList);
    // Post: This list is prepended to revList in reverse order,
    // and this list is empty.

public:
    void setRest(shared_ptr<ListCS<T>> newRest);
    // Post: The rest of this list is set to newRest.

    void toStream(ostream &os) const;
    // Post: os displays a string representation of this list.

    shared_ptr<ListCS<T>> unZip();
    // Post: This is every other element of this list starting with the first.
    // A shared_ptr to a list with every other element of this list starting with the second is returned.

    void zip(ListCS<T> &other);
    // Post: This list is a perfect shuffle of this list and other
    // starting with the first element of this.
    // other is the empty list (cut zip, as opposed to copy zip).
};

// ========= AcsNode =========
template<class T>
class AcsNode {
public:
    virtual ~AcsNode() = default;

    virtual void append(ListCS<T> &owner, T const &data) = 0;
    virtual void clear(ListCS<T> &owner) = 0;
    virtual void concat(ListCS<T> &owner, ListCS<T> &suffix) = 0;
    virtual bool contains(T const &data) const = 0;
    virtual shared_ptr<AcsNode<T>>  copyHead() = 0;
    virtual bool equals(ListCS<T> const &rhs) const = 0;
    virtual bool equalsHelper(T const &first, ListCS<T> const &rest) const = 0;
    virtual T &first() = 0;
    virtual T const &first() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int length() const = 0;
    virtual T const &max() const = 0;
    virtual T const &maxHelper(T const &val) const = 0;
    virtual void prepend(ListCS<T> &owner, T const &data) = 0;
    virtual T remFirst(ListCS<T> &owner) = 0;
    virtual T remLast(ListCS<T> &owner) = 0;
    virtual T remLastHelper(ListCS<T> &owner, ListCS<T> &previous) = 0;
    virtual void remove(ListCS<T> &owner, T const &data) = 0;
    virtual shared_ptr<ListCS<T>> rest() = 0;
    virtual shared_ptr<ListCS<T>> const rest() const = 0;
    virtual void reverse(ListCS<T> &owner) = 0;
    virtual void reverseHelper(ListCS<T> &owner, ListCS<T> &revList) = 0;
    virtual void setRest(ListCS<T> &owner, shared_ptr<ListCS<T>> newRest) = 0;
    virtual void toStream(ostream &os) const = 0;
    virtual void toStreamHelper(ostream &os) const = 0;
    // Post: A string representation of this list is returned
    // except for the leading open parenthesis "(", which is omitted.
    virtual shared_ptr<ListCS<T>> unZip(ListCS<T> &owner) = 0;
    virtual void zip(ListCS<T> &owner, ListCS<T> &other) = 0;
};

// ========= MTcsNode =========
template<class T>
class MTcsNode : public AcsNode<T> {
    friend class ListCS<T>;
    friend class NEcsNode<T>;

private: // Constructor
    MTcsNode() = default;

public: //constuctor
    MTcsNode(MTcsNode<T> const &rhs) = delete; // Disabled.

public:
    void append(ListCS<T> &owner, T const &data) override;
    void clear(ListCS<T> &owner) override;
    void concat(ListCS<T> &owner, ListCS<T> &suffix) override;
    bool contains(T const &data) const override;
    shared_ptr<AcsNode<T>>  copyHead() override;
    bool equals(ListCS<T> const &rhs) const override;
    bool equalsHelper(T const &first, ListCS<T> const &rest) const override;
    T &first() override;
    T const &first() const override;
    bool isEmpty() const override;
    int length() const override;
    T const &max() const override;
    T const &maxHelper(T const &val) const override;
    MTcsNode &operator=(MTcsNode const &rhs) = delete; // Disabled for node.
    void prepend(ListCS<T> &owner, T const &data) override;
    T remFirst(ListCS<T> &owner) override;
    T remLast(ListCS<T> &owner) override;
    T remLastHelper(ListCS<T> &owner, ListCS<T> &previous) override;
    void remove(ListCS<T> &owner, T const &data) override;
    shared_ptr<ListCS<T>> rest() override;
    shared_ptr<ListCS<T>> const rest() const override;
    void reverse(ListCS<T> &owner) override;
    void reverseHelper(ListCS<T> &owner, ListCS<T> &revList) override;
    void setRest(ListCS<T> &owner, shared_ptr<ListCS<T>> newRest) override;
    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;
    shared_ptr<ListCS<T>> unZip(ListCS<T> &owner) override;
    void zip(ListCS<T> &owner, ListCS<T> &other) override;
};

// ========= NEcsNode =========
template<class T>
class NEcsNode : public AcsNode<T> {
    friend class ListCS<T>;
    friend class MTcsNode<T>;

private:
    T _data;
    shared_ptr<ListCS<T>> _rest;

private: // Constructors
    explicit NEcsNode(T const &data);
    // Post: _data is data.

    NEcsNode(T data, shared_ptr<AcsNode<T>> node);
    // Post: _data is data and _rest._head points to node.

    explicit NEcsNode(shared_ptr<const NEcsNode<T>> rhs);
    // Post: _data is rhs->_data and _rest is rhs->_rest.

public:
    void append(ListCS<T> &owner, T const &data) override;
    void clear(ListCS<T> &owner) override;
    void concat(ListCS<T> &owner, ListCS<T> &suffix) override;
    bool contains(T const &data) const override;
    shared_ptr<AcsNode<T>>  copyHead() override;
    bool equals(ListCS<T> const &rhs) const override;
    bool equalsHelper(T const &first, ListCS<T> const &rest) const override;
    T &first() override;
    T const &first() const override;
    bool isEmpty() const override;
    int length() const override;
    T const &max() const override;
    T const &maxHelper(T const &val) const override;
    NEcsNode &operator=(NEcsNode<T> const &rhs) = delete; // Disabled for node.
    void prepend(ListCS<T> &owner, T const &data) override;
    T remFirst(ListCS<T> &owner) override;
    T remLast(ListCS<T> &owner) override;
    T remLastHelper(ListCS<T> &owner, ListCS<T> &previous) override;
    void remove(ListCS<T> &owner, T const &data) override;
    shared_ptr<ListCS<T>> rest() override;
    shared_ptr<ListCS<T>> const rest() const override;
    void reverse(ListCS<T> &owner) override;
    void reverseHelper(ListCS<T> &owner, ListCS<T> &revList) override;
    void setRest(ListCS<T> &owner, shared_ptr<ListCS<T>> newRest) override;
    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;
    shared_ptr<ListCS<T>> unZip(ListCS<T> &owner) override;
    void zip(ListCS<T> &owner, ListCS<T> &other) override;
};

// ========= Constructors =========
template<class T>
ListCS<T>::ListCS() : _head(new MTcsNode<T>()) {}

template<class T>
ListCS<T>::ListCS(shared_ptr<AcsNode<T>> node) :
    _head(node) {
}

template<class T>
NEcsNode<T>::NEcsNode(T const &data) :
    _data(data),
    _rest(make_shared<ListCS<T>>()) {
}

template<class T>
NEcsNode<T>::NEcsNode(T data, shared_ptr<AcsNode<T>> node) :
    NEcsNode(data) {
    _rest->_head = node;
}

template<class T>
NEcsNode<T>::NEcsNode(shared_ptr<const NEcsNode<T>> rhs) :
    _data(rhs->_data),
    _rest(rhs->_rest) {
}

// ========= append =========
template<class T>
void ListCS<T>::append(T const &data) {
    _head->append(*this, data);
}

template<class T>
void MTcsNode<T>::append(ListCS<T> &owner, T const &data) {
    owner._head.reset(new NEcsNode<T>(data));
}

template<class T>
void NEcsNode<T>::append(ListCS<T> &owner, T const &data) {
    _rest->append(data);
}

// ========= clear =========
template<class T>
void ListCS<T>::clear() {
    _head.reset(new MTcsNode<T>());
    // tfw automatic garbage collection

}

template<class T>
void MTcsNode<T>::clear(ListCS<T> &owner) {
}

template<class T>
void NEcsNode<T>::clear(ListCS<T> &owner) {
}

// ========= concat =========
template<class T>
void ListCS<T>::concat(ListCS<T> &suffix) {
    cerr << "ListCS<T>::concat: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void MTcsNode<T>::concat(ListCS<T> &owner, ListCS<T> &suffix) {
    cerr << "MTcsNode<T>::concat: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::concat(ListCS<T> &owner, ListCS<T> &suffix) {
    cerr << "NEcsNode<T>::concat: Exercise for the student." << endl;
    throw -1;
}

// ========= contains =========
template<class T>
bool ListCS<T>::contains(T const &data) const {
    return _head->contains(data);
}

template<class T>
bool MTcsNode<T>::contains(T const &data) const {
    return false;
}

template<class T>
bool NEcsNode<T>::contains(T const &data) const {
    if (data == _data) {
        return true;
    }
    return _rest->contains(data);
}

// ========= copyHead =========
template<class T>
shared_ptr<AcsNode<T>> ListCS<T>::copyHead(ListCS<T> const &rhs) {
    return rhs._head->copyHead();
}

template<class T>
shared_ptr<AcsNode<T>>  MTcsNode<T>::copyHead() {
    return shared_ptr<MTcsNode<T>>(new MTcsNode<T>());
}

template<class T>
shared_ptr<AcsNode<T>>  NEcsNode<T>::copyHead() {
    return shared_ptr<NEcsNode<T>>(new NEcsNode<T>(_data, _rest->_head->copyHead()));
}

// ========= equals =========
// tbh i prefer to do everything in the equals class itself, it makes life easier for
// me if i don't have to use equalHelper()
// fight me if you must
template<class T>
bool ListCS<T>::equals(ListCS<T> const &rhs) const {
    if(rhs.isEmpty() || isEmpty())
        return isEmpty() && rhs.isEmpty();
    return _head->equals(rhs);
}

template<class T>
bool MTcsNode<T>::equals(ListCS<T> const &rhs) const {
    return rhs.isEmpty();
}

template<class T>
bool NEcsNode<T>::equals(ListCS<T> const &rhs) const {
    if (rhs.isEmpty())
        return isEmpty();
//    cout << rhs.first() << " == " << this->first() << endl;
    if (rhs.first() == this->first())
        return _rest->equals(*rhs.rest());
    return false;
}

// --------- equalsHelper ---------
template<class T>
bool ListCS<T>::equalsHelper(T const &first, ListCS<T> const &rest) const {
//    cout << "ListCS<T> equalsHelper is doing things. first == " << first << " and _head->first() == " << _head->first() << endl;
//    return first == _head->first() && _head->equals(rest);
    cerr << "ListCS<T>::equalsHelper: nani!?" << endl;
}

template<class T>
bool MTcsNode<T>::equalsHelper(T const &first, ListCS<T> const &rest) const {
//    cout << "MTcsNode<T> equalsHelper (they aren't equal lmao)" << endl;
//    return rest.isEmpty();
    cerr << "MTcsNode<T>::equalsHelper: get out of here!" << endl;

}

template<class T>
bool NEcsNode<T>::equalsHelper(T const &first, ListCS<T> const &rest) const {
    cerr << "NEcsNode<T>::equalsHelper: this isn't right!" << endl;
}

// ========= first =========
template<class T>
T &ListCS<T>::first() {
    return _head->first();
}

template<class T>
T &MTcsNode<T>::first() {
    cerr << "MTcsNode<T>::first: list is empty." << endl;
    throw -1;
}

template<class T>
T &NEcsNode<T>::first() {
    return _data;
}

// ========= first const =========
template<class T>
T const &ListCS<T>::first() const {
    return _head->first();
}

template<class T>
T const &MTcsNode<T>::first() const {
    cerr << "MTcsNode<T>::first: list is empty." << endl;
    throw -1;
}

template<class T>
T const &NEcsNode<T>::first() const {
    return _data;
}

// ========= isEmpty =========
template<class T>
bool ListCS<T>::isEmpty() const {
    return _head->isEmpty();
}

template<class T>
bool MTcsNode<T>::isEmpty() const {
    return true;
}

template<class T>
bool NEcsNode<T>::isEmpty() const {
    return false;
}

// ========= length =========
template<class T>
int ListCS<T>::length() const {
    return _head->length();
}

template<class T>
int MTcsNode<T>::length() const {
    return 0;
}

template<class T>
int NEcsNode<T>::length() const {
    return 1 + _rest->length();
}

// ========= max =========
template<class T>
T const &ListCS<T>::max() const {
    return _head->max();
}

template<class T>
T const &MTcsNode<T>::max() const {
    cerr << "max precondition violated: An empty list has no maximum." << endl;
    throw -1;
}

template<class T>
T const &NEcsNode<T>::max() const {
    return _rest->maxHelper(_data);
}

// --------- maxHelper ---------
template<class T>
T const &ListCS<T>::maxHelper(T const &val) const {
    return _head->maxHelper(val);
}

template<class T>
T const &MTcsNode<T>::maxHelper(T const &val) const {
    return val;
}

template<class T>
T const &NEcsNode<T>::maxHelper(T const &val) const {
    return _data > val ? _rest->maxHelper(_data) : _rest->maxHelper(val);
}

// ========= operator= =========
template<class T>
ListCS<T> &ListCS<T>::operator=(const ListCS &rhs) {
    if (this != &rhs) { // In case someone writes myList = myList;
        _head = copyHead(rhs);
    }
    return *this;
}

// ========= operator== =========
template<class T>
bool operator==(ListCS<T> const &lhs, ListCS<T> const &rhs) {
    return lhs.equals(rhs);
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, ListCS<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= prepend =========
template<class T>
void ListCS<T>::prepend(T const &data) {
    _head->prepend(*this, data);
}

template<class T>
void MTcsNode<T>::prepend(ListCS<T> &owner, T const &data) {
    // Assert: owner._head is a shared_ptr of this MTcsNode
    auto oldOwnerHead = owner._head;
    owner._head.reset(new NEcsNode<T>(data, oldOwnerHead));
}

template<class T>
void NEcsNode<T>::prepend(ListCS<T> &owner, T const &data) {
    auto oldOwnerHead = owner._head;
    owner._head.reset(new NEcsNode<T>(data, oldOwnerHead));
}

// ========= remFirst =========
template<class T>
T ListCS<T>::remFirst() {
    return _head->remFirst(*this);
}

template<class T>
T MTcsNode<T>::remFirst(ListCS<T> &owner) {
    cerr << "MTcsNode<T>::remFirst: list is empty." << endl;
    throw -1;
}

template<class T>
T NEcsNode<T>::remFirst(ListCS<T> &owner) {
//    cout << "data == " << _data << endl;
    T temp = _data;
    owner = *_rest;
    return temp;
}

// ========= remLast =========
// no helper methods needed (:

template<class T>
T ListCS<T>::remLast() {
    return _head->remLast(*this);
}

template<class T>
T MTcsNode<T>::remLast(ListCS<T> &owner) {
    cerr << "MTcsNode<T>::remLast: list is empty." << endl;
    throw -1;
}

template<class T>
T NEcsNode<T>::remLast(ListCS<T> &owner) {
//    cout << "Current value == " << _data << endl;
    if(rest()->isEmpty()) {
        return owner.remFirst();
    }
    return _rest->remLast();
}

// --------- remLastHelper ---------
template<class T>
T ListCS<T>::remLastHelper(ListCS<T> &previous) {
    cerr << "ListCS<T>::remLastHelper: not supposed to be here." << endl;
}

template<class T>
T MTcsNode<T>::remLastHelper(ListCS<T> &owner, ListCS<T> &previous) {
    cerr << "MTcsNode<T>::remLastHelper: trespassing on unused functions." << endl;
}

template<class T>
T NEcsNode<T>::remLastHelper(ListCS<T> &owner, ListCS<T> &previous) {
    cerr << "NEcsNode<T>::remLastHelper: this function is closed." << endl;
}

// ========= remove =========
template<class T>
void ListCS<T>::remove(T const &data) {
    _head->remove(*this, data);
}

template<class T>
void MTcsNode<T>::remove(ListCS<T> &owner, T const &data) {
}

template<class T>
void NEcsNode<T>::remove(ListCS<T> &owner, T const &data) {
    if (data == _data) {
        remFirst(*rest());
    }
    _rest->remove(data);
}

// ========= rest =========
template<class T>
shared_ptr<ListCS<T>> ListCS<T>::rest() {
    return _head->rest();
}

template<class T>
shared_ptr<ListCS<T>> MTcsNode<T>::rest() {
    cerr << "rest precondition violated: An empty list has no rest." << endl;
    throw -1;
}

template<class T>
shared_ptr<ListCS<T>> NEcsNode<T>::rest() {
    return _rest;
}

// ========= rest const =========
template<class T>
shared_ptr<ListCS<T>> const ListCS<T>::rest() const {
    return _head->rest();
}

template<class T>
shared_ptr<ListCS<T>> const MTcsNode<T>::rest() const {
    cerr << "rest precondition violated: An empty list has no rest." << endl;
    throw -1;
}
template<class T>
shared_ptr<ListCS<T>> const NEcsNode<T>::rest() const {
    return _rest;
}

// ========= reverse =========
template<class T>
void ListCS<T>::reverse() {
    _head->reverse(*this);
}

template<class T>
void MTcsNode<T>::reverse(ListCS<T> &owner) {
}

template<class T>
void NEcsNode<T>::reverse(ListCS<T> &owner) {
    auto revList = new ListCS<T>();
    reverseHelper(owner, *revList);
    owner = *revList;
}

// --------- reverseHelper ---------
template<class T>
void ListCS<T>::reverseHelper(ListCS<T> &revList) {
    cerr << "ListCS<T>::reverseHelper: tf how'd you get here!?!?" << endl;
}

template<class T>
void MTcsNode<T>::reverseHelper(ListCS<T> &owner, ListCS<T> &revList) {
    cerr << "MTcsNode<T>::reverseHelper: what life choices led you to this function?" << endl;
}

template<class T>
void NEcsNode<T>::reverseHelper(ListCS<T> &owner, ListCS<T> &revList) {
    // we do it with a loop. sorry recursion
    while(!owner.isEmpty()) {
//        cout << "pre reverse step: owner == " << owner << " and revList == " << revList << endl;
        auto temp = owner.remFirst();
        revList.prepend(temp);
//        cout << "post reverse step: owner == " << owner << " and revList == " << revList << endl;
    }
}

// ========= setRest =========
template<class T>
void ListCS<T>::setRest(shared_ptr<ListCS<T>> newRest) {
    _head->setRest(*this, newRest);
}

template<class T>
void MTcsNode<T>::setRest(ListCS<T> & , shared_ptr<ListCS<T>> ) {
    cerr << "setRest precondition violated: "
         << "An empty list has no rest." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::setRest(ListCS<T> &owner, shared_ptr<ListCS<T>> newRest) {
    _rest = newRest;
}

// ========= toStream =========
template<class T>
void ListCS<T>::toStream(ostream &os) const {
    _head->toStream(os);
}

template<class T>
void MTcsNode<T>::toStream(ostream &os) const {
    os << "()";
}

template<class T>
void NEcsNode<T>::toStream(ostream &os) const {
    os << "(" << _data;
    _rest->_head->toStreamHelper(os);
}

// --------- toStreamHelper ---------
template<class T>
void MTcsNode<T>::toStreamHelper(ostream &os) const {
    os << ")";
}

template<class T>
void NEcsNode<T>::toStreamHelper(ostream &os) const {
    os << ", " << _data;
    _rest->_head->toStreamHelper(os);
}

// ========= unZip =========
template<class T>
shared_ptr<ListCS<T>> ListCS<T>::unZip() {
    cerr << "ListCS<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

template<class T>
shared_ptr<ListCS<T>> MTcsNode<T>::unZip(ListCS<T> &owner) {
    cerr << "MTcsNode<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

template<class T>
shared_ptr<ListCS<T>> NEcsNode<T>::unZip(ListCS<T> &owner) {
    cerr << "NEcsNode<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

// ========= zip =========
template<class T>
void ListCS<T>::zip(ListCS<T> &other) {
    cerr << "ListCS<T>::zip: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void MTcsNode<T>::zip(ListCS<T> &owner, ListCS<T> &other) {
    cerr << "MTcsNode<T>::zip(ListCS: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::zip(ListCS<T> &owner, ListCS<T> &other) {
    cerr << "NEcsNode<T>::zip: Exercise for the student." << endl;
    throw -1;
}

#endif
