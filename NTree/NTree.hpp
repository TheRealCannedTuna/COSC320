// File: NTree/NTree.hpp

#ifndef NTree_HPP_
#define NTree_HPP_

#include <iostream>

#include "VectorT.hpp"
#include "ANTreeVis.hpp"

using namespace std;

template<class T>
class NTree {
private:
    shared_ptr<VectorT<T>> _data;
    shared_ptr<VectorT<shared_ptr<NTree<T>>>> _children;

private: // Constructors
    NTree(NTree<T> const &rhs);
    // Copy constructor disabled.

    NTree(shared_ptr<NTree<T>> left, T const &val, shared_ptr<NTree<T>> right);
    // Pre: left and right are not nullptr.
    // Post: this tree has one root element with left as the left subtree
    // and right as the right subtree.

    NTree(shared_ptr<VectorT<T>> data, shared_ptr<VectorT<shared_ptr<NTree<T>>>> children);
    // Pre: data and children are not nullptr.
    // Post: The data vector are the data
    // and the children vector are the children of this tree.

public: // Constructors
    NTree();
    // Post: This tree is initialized to be empty.

    NTree(T const &val);
    // Post: This tree is initialized to have a single value val
    // and empty left and right children.

public:
    void accept(ANTreeVis<T> &visitor);
    void accept(ANTreeVis<T> &visitor) const;

    T const &getData(int i) const;
    // Post: The data value at position i is returned.

    shared_ptr<NTree<T>> getChild(int i) const;
    // Post: A pointer to the child tree at position i is returned.

    NTree &operator=(NTree const &rhs); // TODO

    void spliceAt(int i, NTree<T>& tree);
    // Pre: 0 =< i <= _data->size().
    // Post: tree is spliced into this tree at position i.
    // Post: If tree is empty, this tree is unchanged.
    // Post: tree is the empty tree.

    void splitDownAt(int i);
    // Pre:  If _data->size() != 0, 0 <= i < _data->size().
    // Post: If _data->size() == 0, nothing is done.
    // Post: If _data->size() != 1, the element at position i is split down.
    // Post: If _data->size() == 1, the single value is deleted, and
    //                              this tree is empty.

    void splitUpAt(int i);
    // Pre:  If _data->size() > 1,  0 <= i < _data->size().
    // Post: If _data->size() > 1,  the element at position i is split up.
    // Post: If _data->size() <= 1, nothing is done.
};

// ========= Private constructors =========
template<class T>
NTree<T>::NTree(shared_ptr<NTree<T>> left, T const &val, shared_ptr<NTree<T>> right) :
    _data(new VectorT<T>), _children(new VectorT<shared_ptr<NTree<T>>>) {
    _data->append(val);
    _children->append(left);
    _children->append(right);
}

template<class T>
NTree<T>::NTree(shared_ptr<VectorT<T>> data,
                shared_ptr<VectorT<shared_ptr<NTree<T>>>> children) :
    _data(data), _children(children) {
}

// ========= Public constructors =========
template<class T>
NTree<T>::NTree() :
    _data(new VectorT<T>), _children(new VectorT<shared_ptr<NTree<T>>>) {
}

template<class T>
NTree<T>::NTree(T const &val) :
    _data(new VectorT<T>), _children(new VectorT<shared_ptr<NTree<T>>>) {
    _data->append(val);
    _children->append(make_shared<NTree<T>>());
    _children->append(make_shared<NTree<T>>());
}

// ========= Getters =========
template<class T>
T const &NTree<T>::getData(int i) const {
    return (*_data)[i];
}

template<class T>
shared_ptr<NTree<T>> NTree<T>::getChild(int i) const {
    return (*_children)[i];
}

// ========= spliceAt =========
template<class T>
void NTree<T>::spliceAt(int i, NTree<T>& tree) {
    if (i < 0 || _data->size() < i) {
        cerr << "spliceAt precondition 0 =< i <= _data->size() violated." << endl;
        cerr << "i == " << i << ", _data->size() == " << _data->size() << endl;
        throw -1;
    }
    int treeSize = tree._data->size();
    if (treeSize == 0) { // Tree being inserted is empty.
        return;
    }
    if (_data->size() == 0) { // Receiver tree is empty. There is no (*_children)[0], so insert instead.
        _children->insert(i, tree._children->remove(treeSize--));
    } else {
        (*_children)[i] = tree._children->remove(treeSize--);
    }
    for (int k = treeSize; k >= 0; k--) {
//        cerr << "Exercise for the student." << endl;
//        throw -1;
        _data->insert(i, tree._data->remove(k));
        _children->insert(i, tree._children->remove(k));
    }
}

// ========= splitDownAt =========
template<class T>
void NTree<T>::splitDownAt(int i) {
    if (_data->size() == 0) {
        return;
    }
    if (i < 0 || _data->size() <= i) {
        cerr << "splitDownAt precondition 0 <= i < _data->size() violated." << endl;
        cerr << "i == " << i << ", _data->size() == " << _data->size() << endl;
        throw -1;
    }
    if (_data->size() == 1) {
        _data->remove(0); // _data is now empty.
    } else {
        auto newChild = shared_ptr<NTree<T>>(new NTree<T>(getChild(i),
                                                          _data->remove(i),
                                                          getChild(i + 1)));
        cerr << "Exercise for the student." << endl;
        throw -1;
    }
}

// ========= splitUpAt =========
template<class T>
void NTree<T>::splitUpAt(int i) {
    if (_data->size() <= 1) {
        return;
    }
    if (i < 0 || _data->size() <= i) {
        cerr << "splitUpAt precondition 0 <= i < _data->size() violated." << endl;
        cerr << "i == " << i << ", _data->size() == " << _data->size() << endl;
        throw -1;
    }
    // Build a new left subtree with new data and new children:
    auto newData = make_shared<VectorT<T>>();
    auto newChildren = make_shared<VectorT<shared_ptr<NTree<T>>>>();
    T rootDat = _data->remove(i); // This element will be at the new root.
    for (int k = 0; k < i; k++) {
        newData->append(_data->remove(0));
        newChildren->append(_children->remove(0));
    }
    newChildren->append(_children->remove(0));
    shared_ptr<NTree<T>> left, right;
    if (newData->size() > 0) {
        left = shared_ptr<NTree<T>>(new NTree<T>(newData, newChildren));
    } else {
        left = newChildren->remove(0);
    }
    if (_data->size() > 0) {
        right = shared_ptr<NTree<T>>(new NTree<T>(_data, _children));
    } else {
        right = _children->remove(0);
    }
    _data = make_shared<VectorT<T>>();
    _data->append(rootDat);
    _children = make_shared<VectorT<shared_ptr<NTree<T>>>>();
    _children->append(left);
    _children->append(right);

}

// ========= accept =========
template<class T>
void NTree<T>::accept(ANTreeVis<T> &visitor) {
    visitor.caseAt(_data->size(), *this);
}

// ========= accept const =========
template<class T>
void NTree<T>::accept(ANTreeVis<T>& visitor) const {
    visitor.caseAt(_data->size(), *this);
}

// ========= operator= =========

// TODO.

#endif
