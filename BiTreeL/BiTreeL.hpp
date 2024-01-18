// File: BiTreeL/BiTreeL.hpp

#ifndef BITREEL_HPP_
#define BITREEL_HPP_

#include <iostream> // ostream.
#include <memory>
using namespace std;

template<class T> class LNode; // Forward declaration.

// ========= BiTreeL =========
template<class T>
class BiTreeL {
    friend class LNode<T>;

private:
    shared_ptr<LNode<T>> _root;

public:
    BiTreeL() = default;
    // Post: This tree is initialized to be empty.

    BiTreeL(BiTreeL<T> const &rhs) = delete;
    // Copy constructor disabled.

public:
    void clear();
    // Post: This tree is cleared to the empty tree.

    bool contains(T const &data) const;
    // Post: true is returned if val is contained in this tree;
    // otherwise, false is returned.

private:
    shared_ptr<LNode<T>> copyRoot(BiTreeL<T> const &rhs);
    // Post: A deep copy of the root of rhs is returned.

public:
    bool equals(BiTreeL<T> const &rhs) const;
    // Post: true is returned if this tree equals tree rhs;
    // otherwise, false is returned.
    // Two trees are equal if they contain the same number
    // of equal elements with the same shape.

    int height() const;
    // Post: The height of the host tree is returned.

    void inOrder(ostream &os) const;
    // Post: An inorder representation of this tree is sent to os.

    void insertRoot(T const &data);
    // Pre: This tree is empty.
    // Post: This tree has one root node containing data.

    bool isEmpty() const;
    // Post: true is returned if this tree is empty;
    // otherwise, false is returned.

    bool leftIsEmpty() const;
    // Pre: This tree is not empty.
    // Post: true is returned if the left subtree of this tree is empty;
    // otherwise, false is returned.

    T const &max() const;
    // Pre: This tree is not empty.
    // Post: The maximum element of this tree is returned.

    int numLeaves() const;
    // Post: The number of leaves of the host tree is returned.

    int numNodes() const;
    // Post: The number of nodes of the host tree is returned.

    BiTreeL & operator=(BiTreeL<T> const &rhs);
    // Post: A deep copy of rhs is returned.

    void postOrder(ostream &os) const;
    // Post: A postorder representation of this tree is sent to os.

    void preOrder(ostream &os) const;
    // Post: A preorder representation of this tree is sent to os.

    void remLeaves();
    // Post: The leaves are removed from this tree.

    T remRoot();
    // Pre: This tree is not empty.
    // Pre: The root of this tree has at least one empty child.
    // Post: The root node is removed from this tree and its
    // element is returned.

    bool rightIsEmpty() const;
    // Pre: This tree is not empty.
    // Post: true is returned if the right subtree of this tree is empty;
    // otherwise, false is returned.

    T const &root() const;
    // Pre: This tree is not empty.
    // Post: The root element of this tree is returned.

    void setLeft(BiTreeL<T> &subTree);
    // Pre: This tree is not empty.
    // Post: The left child of this tree is subTree.
    // subTree is the empty tree (cut setLeft, as opposed to copy setLeft).

    void setRight(BiTreeL<T> &subTree);
    // Pre: This tree is not empty.
    // Post: The right child of this tree is subTree.
    // subTree is the empty tree (cut setRight, as opposed to copy setRight).

    void setRoot(T const &data);
    // Pre: This tree is not empty.
    // Post: The root element of this tree is changed to data.

    void toStream(ostream &os) const;
    // Post: A string representation of this tree is sent to os.
};

// ========= LNode =========
template<class T>
class LNode {
    friend class BiTreeL<T>;

private:
    shared_ptr<LNode> _left;
    T _data;
    shared_ptr<LNode> _right;

private:
    LNode(T const &data);

private:
    bool contains(T const &data) const;
    shared_ptr<LNode<T>> copyRoot();
    // Post: A deep copy of this node is returned.
    bool equals(shared_ptr<const LNode<T>> rhs) const;
    int height() const;
    void inOrder(ostream &os) const;
    T const &max() const;
    int numLeaves() const;
    int numNodes() const;
    void postOrder(ostream &os) const;
    void preOrder(ostream &os) const;
    void remLeaves();
    T const &root() const;
    void setLeft(BiTreeL<T> &subTree);
    void setRight(BiTreeL<T> &subTree);
    void setRoot(T const &data);
    void toStream(string prRight, string prRoot, string prLeft, ostream &os) const;
};

// ========= Constructor =========
template<class T>
LNode<T>::LNode(T const &data):
    _data(data) {
}

// ========= clear =========
template<class T>
void BiTreeL<T>::clear() {
    _root = nullptr;
}

// ========= contains =========
template<class T>
bool BiTreeL<T>::contains(T const &data) const {
    if (_root == nullptr)
        return false;
    return _root->contains(data);
}

template<class T>
bool LNode<T>::contains(T const &data) const {
    if (data == _data) return true;
    bool containsLeft, containsRight = false;
    if (_left) {
        containsLeft = _left->contains(data);
    }
    if (_right) {
        containsRight = _right->contains(data);
    }
    return containsLeft || containsRight;
}

// ========= copyRoot =========
template<class T>
shared_ptr<LNode<T>> BiTreeL<T>::copyRoot(BiTreeL<T> const &rhs) {
    return rhs.isEmpty() ? nullptr : rhs._root->copyRoot();
}

template<class T>
shared_ptr<LNode<T>> LNode<T>::copyRoot() {
    shared_ptr<LNode<T>> result = shared_ptr<LNode<T>>(new LNode<T >(_data));
    if (_left) {
        result->_left = _left->copyRoot();
    }
    if (_right) {
        result->_right = _right->copyRoot();
    }
    return result;
}

// ========= equals =========
template<class T>
bool BiTreeL<T>::equals(BiTreeL<T> const &rhs) const {
    if (!_root) return rhs.isEmpty();
    return !rhs.isEmpty() && _root->equals(rhs._root);
}

template<class T>
bool LNode<T>::equals(shared_ptr<const LNode<T>> rhs) const {
//    bool equalsLeft = _left == nullptr && rhs->_left == nullptr;
//    bool equalsRight = _right == nullptr && rhs->_right == nullptr;
//    if (_left && rhs->_left) {
//        equalsLeft = _left == rhs->_left;
//    }
//    if (_right && rhs->_right) {
//        equalsRight = _right == rhs->_right;
//    }
//    return _data == rhs->_data && equalsLeft && equalsRight;
    //


    if ((!_left && rhs->_left) || (_left && !rhs->_left)) {
        return false;
    }
    if ((!_right && rhs->_right) || (_right && !rhs->_right)) {
        return false;
    }
    // holy shit this is uglier than me right after i wake up
    // but it makes it pass the unit test so i guess eh?
    return _left && _right ? _data == rhs->_data && _left->equals(rhs->_left) && _right->equals(rhs->_right) :
        (!_left && !_right ? _data == rhs->_data :
            (_left && !_right ? _data == rhs->_data && _left->equals(rhs->_left) :
                _data == rhs->_data && _right->equals(rhs->_right)));
}

// ========= height =========
template<class T>
int BiTreeL<T>::height() const {
    if (!_root) return 0;
    return _root->height();
}

template<class T>
int LNode<T>::height() const {
    int height = 1;
    if (_left)
        height = height + _left->height();
    int rightHeight;
    if (_right)
        rightHeight = 1 + _right->height();
    return height > rightHeight ? height : rightHeight;
}

// ========= inOrder =========
template<class T>
void BiTreeL<T>::inOrder(ostream &os) const {
    if (_root)
        _root->inOrder(os);
}

template<class T>
void LNode<T>::inOrder(ostream &os) const {
    if (_left)
        _left->inOrder(os);
    os << _data << "  ";
    if (_right)
        _right->inOrder(os);
}

// ========= insertRoot =========
template<class T>
void BiTreeL<T>::insertRoot(T const &data) {
    if (_root != nullptr) {
        cerr << "insertRoot precondition violated: Cannot insert root into a non empty tree" << endl;
        throw -1;
    }
    _root = shared_ptr<LNode<T>>(new LNode<T>(data));
}

// ========= isEmpty =========
template<class T>
bool BiTreeL<T>::isEmpty() const {
    return _root == nullptr;
}

// ========= leftIsEmpty =========
template<class T>
bool BiTreeL<T>::leftIsEmpty() const {
    if (_root == nullptr) {
        cerr << "Precondition violated: Cannot test left subtree of an empty tree." << endl;
        throw -1;
    }
    return _root->_left == nullptr;
}

// ========= max =========
template<class T>
T const &BiTreeL<T>::max() const {
    if (_root == nullptr) {
        cerr << "Precondition violated: An empty tree has no maximum." << endl;
        throw -1;
    }
    return _root->max();
}

template<class T>
T const &LNode<T>::max() const {
    T const &leftMax = (_left == nullptr) ? _data : _left->max();
    T const &rightMax = (_right == nullptr) ? _data : _right->max();
    return (leftMax > rightMax) ?
        ((leftMax > _data) ? leftMax : _data) :
        ((rightMax > _data) ? rightMax : _data);
}

// ========= numLeaves =========
template<class T>
int BiTreeL<T>::numLeaves() const {
    if (_root)
        return _root->numLeaves();
    return 1;
}

template<class T>
int LNode<T>::numLeaves() const {
    int numLeaves = 0;
    if (!(_left || _right))
        numLeaves = 1;
    if (_left)
        numLeaves = numLeaves + _left->numLeaves();
    if (_right)
        numLeaves = numLeaves + _right->numLeaves();
    return numLeaves;
}

// ========= numNodes =========
template<class T>
int BiTreeL<T>::numNodes() const {
    return _root == nullptr ? 0 : _root->numNodes();
}

template<class T>
int LNode<T>::numNodes() const {
    int result = 1;
    if (_left) {
        result += _left->numNodes();
    }
    if (_right) {
        result += _right->numNodes();
    }
    return result;
}

// ========= operator= =========
template<class T>
BiTreeL<T> &BiTreeL<T>::operator=(BiTreeL<T> const &rhs) {
    if (this != &rhs) { // In case someone writes myTree = myTree;
        _root = copyRoot(rhs);
    }
    return *this;
}

// ========= operator== =========
template<class T>
bool operator==(BiTreeL<T> const &lhs, BiTreeL<T> const &rhs) {
    return lhs.equals(rhs);
}

// ========= operator<< =========
template<class T>
ostream & operator<<(ostream &os, BiTreeL<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= postOrder =========
template<class T>
void BiTreeL<T>::postOrder(ostream &os) const {
    if (_root)
        _root->postOrder(os);
}

template<class T>
void LNode<T>::postOrder(ostream &os) const {
    if (_left)
        _left->postOrder(os);
    if (_right)
        _right->postOrder(os);
    os << _data << "  ";
}

// ========= preOrder =========
template<class T>
void BiTreeL<T>::preOrder(ostream &os) const {
    if (_root) {
        _root->preOrder(os);
    }
}

template<class T>
void LNode<T>::preOrder(ostream &os) const {
    os << _data << "  ";
    if (_left) {
        _left->preOrder(os);
    }
    if (_right) {
        _right->preOrder(os);
    }
}

// ========= remLeaves =========
template<class T>
void BiTreeL<T>::remLeaves() {
    if (_root) _root->remLeaves();
}

template<class T>
void LNode<T>::remLeaves() {
    _left = nullptr;
    _right = nullptr;
}

// ========= remRoot =========
template<class T>
T BiTreeL<T>::remRoot() {
    if (_root == nullptr) {
        cerr << "remRoot precondition violated: "
             << "Cannot remove root from an empty tree." << endl;
        throw -1;
    }
    if (_root->_left && _root->_right) {
        cerr << "remRoot: there gotta be one empty node." << endl;
        throw -1;
    }
    auto temp = _root;
    if (_root->_left) {
        _root = _root->_left;
    } else {
        _root = _root->_right;
    }
    return temp->_data;
}

// ========= rightIsEmpty =========
template<class T>
bool BiTreeL<T>::rightIsEmpty() const {
    if (_root == nullptr) {
        cerr << "Precondition violated: "
             << "Cannot test right subtree of an empty tree." << endl;
        throw -1;
    }
    return _root->_right == nullptr;
}

// ========= root =========
template<class T>
T const &BiTreeL<T>::root() const {
    if (_root == nullptr) {
        cerr << "root precondition violated: "
             << "An empty tree has no root." << endl;
        throw -1;
    }
    return _root->root();
}

template<class T>
T const &LNode<T>::root() const {
    return _data;
}

// ========= setLeft =========
template<class T>
void BiTreeL<T>::setLeft(BiTreeL<T> &subTree) {
    if (_root == nullptr) {
        cerr << "Precondition violated: "
             << "Cannot set left on an empty tree." << endl;
        throw -1;
    }
    _root->setLeft(subTree);
}

template<class T>
void LNode<T>::setLeft(BiTreeL<T> &subTree) {
    _left = subTree._root;
    subTree._root.reset();
}

// ========= setRight =========
template<class T>
void BiTreeL<T>::setRight(BiTreeL<T> &subTree) {
    if (_root == nullptr) {
        cerr << "Precondition violated: "
             << "Cannot set right on an empty tree." << endl;
        throw -1;
    }
    _root->setRight(subTree);
}

template<class T>
void LNode<T>::setRight(BiTreeL<T> &subTree) {
    _right = subTree._root;
    subTree._root.reset();
}

// ========= setRoot =========
template<class T>
void BiTreeL<T>::setRoot(T const &data) {
    if (!_root) {
        cerr << "setRoot: tree is empty lmao" << endl;
        throw -1;
    }
    _root->setRoot(data);
}

template<class T>
void LNode<T>::setRoot(T const &data) {
    _data = data;
}

// ========= toStream =========
template<class T>
void BiTreeL<T>::toStream(ostream &os) const {
    if (_root == nullptr) {
        os << "*";
    }
    else {
        _root->toStream("", "", "", os);
    }
}

template<class T>
void LNode<T>::toStream(string prRight, string prRoot, string prLeft, ostream &os) const {
    if (_right == nullptr) {
        os << prRight << "     -*" << endl;
    }
    else {
        _right->toStream(prRight + "     ", prRight + "     ", prRight + "    |", os);
    }
    os << prRoot;
    os.fill('-');
    os.width(4);
    os.setf(ios::left, ios::adjustfield);
    os << _data << "|" << endl;
    if (_left == nullptr) {
        os << prLeft << "     -*" << endl;
    }
    else {
        _left->toStream(prLeft + "    |", prLeft + "     ", prLeft + "     ", os);
    }
}

#endif
