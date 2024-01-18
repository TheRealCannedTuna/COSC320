// File: ListCSV/ListCSV.hpp

#ifndef LISTCSV_HPP_
#define LISTCSV_HPP_

#include <iostream>
#include <memory>
using namespace std;

template<class T> class ListCSV;    // Forward declaration.
template<class T> class AcsvNode;   // Forward declaration.
template<class T> class MTcsvNode;  // Forward declaration.
template<class T> class NEcsvNode;  // Forward declaration.

// ======== Abstract visitor for ListCSV ========
template<class T>
class AListCSVVis {
public:
    virtual ~AListCSVVis() = default;
    virtual void emptyCase(ListCSV<T> &host) = 0;
    virtual void nonEmptyCase(ListCSV<T> &host) = 0;
    virtual void emptyCase(ListCSV<T> const &host) = 0; // For const host.
    virtual void nonEmptyCase(ListCSV<T> const &host) = 0; // For const host.
};

template<class T>
class ListCSV {
    friend class MTcsvNode<T>;
    friend class NEcsvNode<T>;

private:
    shared_ptr<AcsvNode<T>> _head; // state of the list.

private: // Constructors
    explicit ListCSV(shared_ptr<AcsvNode<T>> node);
    // Pre: node != nullptr.
    // Post: _head points to node with no allocation.

public: // Constructors
    ListCSV();
    // Post: This list is initialized to be empty.

    ListCSV(ListCSV<T> const &rhs) = delete; // Copy constructor disabled.

public:
    void accept(AListCSVVis<T> &visitor);
    void accept(AListCSVVis<T> &visitor) const;

private:
    shared_ptr<AcsvNode<T>> copyHead(ListCSV<T> const &rhs);
    // Post: A deep copy of the head of rhs is returned.

public:
    T &first();
    T const &first() const;
    // Pre: This list is not empty.
    // Post: The first element of this list is returned.

    ListCSV &operator=(ListCSV const &rhs);
    // Post: A deep copy of rhs is returned.

    void prepend(T const &data);
    // Post: data is prepended to this list.

    T remFirst();
    // Pre: This list is not empty.
    // Post: The first element is removed from this list and returned.

    shared_ptr<ListCSV<T>> rest();
    shared_ptr<ListCSV<T>> const rest() const;
    // Pre: This list is not empty.
    // Post: A shared_ptr to the rest of this list is returned.

    void setRest(shared_ptr<ListCSV<T>> newRest);
    // Pre: This list is not empty.
    // Post: The rest of this list is set to newRest.
};

// ========= AcsvNode =========
template<class T>
class AcsvNode: public enable_shared_from_this<AcsvNode<T>> {
public:
    virtual ~AcsvNode() = default;

    virtual void accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) = 0;
    virtual void accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) = 0;
    virtual shared_ptr<AcsvNode<T>> copyHead() = 0;
    // Post: A deep copy of this node is returned.
    virtual T &first() = 0;
    virtual T const &first() const = 0;
    virtual void prepend(ListCSV<T> &owner, T const &data) = 0; // not virtual after code hoisting.
    virtual T remFirst(ListCSV<T> &owner) = 0;
    virtual shared_ptr<ListCSV<T>> rest() = 0;
    virtual shared_ptr<ListCSV<T>>  const rest() const = 0;
    virtual void setRest(ListCSV<T> &owner, shared_ptr<ListCSV<T>> newRest) = 0;
};

// ========= MTcsvNode =========
template<class T>
class MTcsvNode : public AcsvNode<T> {
    friend class ListCSV<T>;
    friend class NEcsvNode<T>;

private: // Constructors
    MTcsvNode() = default;

public: // Constructors
    MTcsvNode(MTcsvNode<T> const &rhs) = delete; // Disabled.
    MTcsvNode &operator=(MTcsvNode<T> const &rhs) = delete; // Disabled for node.

public:
    void accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) override;
    void accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) override;
    shared_ptr<AcsvNode<T>> copyHead() override;
    T &first() override;
    T const &first() const override;
    void prepend(ListCSV<T> &owner, T const &data) override;
    T remFirst(ListCSV<T> &owner) override;
    shared_ptr<ListCSV<T>> rest() override;
    shared_ptr<ListCSV<T>> const rest() const override;
    void setRest(ListCSV<T> &owner, shared_ptr<ListCSV<T>> newRest)  override;
};

// ========= NEcsvNode =========
template<class T>
class NEcsvNode : public AcsvNode<T> {
    friend class ListCSV<T>;
    friend class MTcsvNode<T>;

private:
    T _data;
    shared_ptr<ListCSV<T>> _rest;

private: // Constructors
    explicit NEcsvNode(T data);
    // Post: _data is data and _rest points to an empty ListCSV.

    NEcsvNode(T data, shared_ptr<AcsvNode<T>> node);
    // Post: _data is data and _rest->_head points to node.

    NEcsvNode(T data,  shared_ptr<ListCSV<T>> rest);
    // Post: _data is data and _rest is rest.

    explicit NEcsvNode(shared_ptr<const NEcsvNode<T>> rhs);
    // Post: _data is rhs->_data and _rest is rhs->_rest.

public:
    void accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) override;
    void accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) override;
    shared_ptr<AcsvNode<T>> copyHead() override;
    T &first() override;
    T const &first() const override;
    NEcsvNode &operator=(NEcsvNode<T> const &rhs) = delete; // Disabled for node.
    void prepend(ListCSV<T> &owner, T const &data) override;
    T remFirst(ListCSV<T> &owner) override;
    shared_ptr<ListCSV<T>> rest() override;
    shared_ptr<ListCSV<T>> const rest() const override;
    void setRest(ListCSV<T> &owner, shared_ptr<ListCSV<T>> newRest)  override;
};

// ========= Constructors =========
template<class T>
ListCSV<T>::ListCSV() :
    _head(new MTcsvNode<T>()) {
}

template<class T>
ListCSV<T>::ListCSV(shared_ptr<AcsvNode<T>> node) :
    _head(node) {
}

template<class T>
NEcsvNode<T>::NEcsvNode(T data) :
    _data(data), _rest(make_shared<ListCSV<T>>()) {
}

template<class T>
NEcsvNode<T>::NEcsvNode(T data, shared_ptr<AcsvNode<T>> node) :
    NEcsvNode(data) {
    _rest->_head = node;
}

template<class T>
NEcsvNode<T>::NEcsvNode(T data, shared_ptr<ListCSV<T>> rest) :
    _data(data), _rest(rest) {
}

template<class T>
NEcsvNode<T>::NEcsvNode(shared_ptr<const NEcsvNode<T>> rhs) :
    _data(rhs->_data), _rest(rhs->_rest) {
}

// ========= accept =========
template<class T>
void ListCSV<T>::accept(AListCSVVis<T> &visitor) {
    _head->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= accept const =========
template<class T>
void ListCSV<T>::accept(AListCSVVis<T> &visitor) const {
    _head->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= copyHead =========
template<class T>
shared_ptr<AcsvNode<T>> ListCSV<T>::copyHead(ListCSV<T> const &rhs) {
    return rhs._head->copyHead();
}

template<class T>
shared_ptr<AcsvNode<T>> MTcsvNode<T>::copyHead() {
    return shared_ptr<MTcsvNode<T>>(new MTcsvNode<T>());
}

template<class T>
shared_ptr<AcsvNode<T>> NEcsvNode<T>::copyHead() {
    return shared_ptr<NEcsvNode<T>>(new NEcsvNode<T >(
                                        _data, _rest->_head->copyHead()));
}

// ========= first =========
template<class T>
T &ListCSV<T>::first() {
    return _head->first();
}

template<class T>
T &MTcsvNode<T>::first() {
    cerr << "MTcsvNode<T>::first: list is empty." << endl;
    throw -1;
}

template<class T>
T &NEcsvNode<T>::first() {
    return _data;
}

// ========= first const =========
template<class T>
T const &ListCSV<T>::first() const {
    return _head->first();
}

template<class T>
T const &MTcsvNode<T>::first() const {
    cerr << "MTcsvNode<T>::first: list is empty." << endl;
    throw -1;
}

template<class T>
T const &NEcsvNode<T>::first() const {
    return _data;
}

// ========= operator= =========
template<class T>
ListCSV<T> &ListCSV<T>::operator=(ListCSV const &rhs) {
    if (this != &rhs) { // In case someone writes myList = myList;
        _head = copyHead(rhs);
    }
    return *this;
}

// ========= prepend =========
template < class T >
void ListCSV<T>::prepend(T const &data) {
    _head->prepend(*this, data);
}

template < class T >
void MTcsvNode<T>::prepend(ListCSV<T> &owner, T const &data) {
    owner._head.reset(new NEcsvNode<T>(data));
}

template < class T >
void NEcsvNode<T>::prepend(ListCSV<T> &owner, T const &data) {
    auto coOwner = shared_ptr<ListCSV<T>>(new ListCSV<T>(this->shared_from_this()));
    owner._head.reset(new NEcsvNode<T>(data, coOwner));
}

// ========= rest =========
template<class T>
shared_ptr<ListCSV<T>> ListCSV<T>::rest() {
    return _head->rest();
}

template<class T>
shared_ptr<ListCSV<T>> MTcsvNode<T>::rest() {
    cerr << "rest precondition violated: "
         << "An empty list has no rest." << endl;
    throw -1;
}

template<class T>
shared_ptr<ListCSV<T>> NEcsvNode<T>::rest() {
    return _rest;
}

// ========= rest const =========
template<class T>
shared_ptr<ListCSV<T>> const ListCSV<T>::rest() const {
    return _head->rest();
}

template<class T>
shared_ptr<ListCSV<T>> const MTcsvNode<T>::rest() const {
    cerr << "rest precondition violated: "
         << "An empty list has no rest." << endl;
    throw -1;
}

template<class T>
shared_ptr<ListCSV<T>> const NEcsvNode<T>::rest() const {
    return _rest;
}

// ========= remFirst =========
template < class T >
T ListCSV<T>::remFirst() {
    return _head->remFirst(*this);
}

template<class T>
T MTcsvNode<T>::remFirst(ListCSV<T> &owner) {
    cerr << "MTcsNode<T>::remFirst: list is empty." << endl;
    throw -1;
}

template<class T>
T NEcsvNode<T>::remFirst(ListCSV<T> &owner) {
    T temp = _data;
    owner = *_rest;
    return temp;
}

// ========= setRest =========
template<class T>
void ListCSV<T>::setRest(shared_ptr<ListCSV<T>> newRest) {
    _head->setRest(*this, newRest);
}

template<class T>
void MTcsvNode<T>::setRest(ListCSV<T> & , shared_ptr<ListCSV<T>> ) {
    cerr << "setRest precondition violated: "
         << "An empty list has no rest." << endl;
    throw -1;
}

template<class T>
void NEcsvNode<T>::setRest(ListCSV<T> &owner, shared_ptr<ListCSV<T>> newRest) {
    _rest = newRest;
}

#endif
