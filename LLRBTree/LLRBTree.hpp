// File: LLRBTree/LLRBTree.hpp

#ifndef LLRBTREE_HPP_
#define LLRBTREE_HPP_

#include <iostream> // ostream.
#include <memory> // shared_ptr.

using namespace std;

template<class T>
class Node; // Forward declaration.

const bool RED = true;
const bool BLACK = false;

// ========= LLRBTree =========
template<class T>
class LLRBTree {
private:
    shared_ptr<Node<T>> _root;

public:
    LLRBTree() = default; //Constructor
    // Post: This left-leaning red-black tree
    // is initialized to be empty.

    bool contains(T const &data);
    // Post: Returns true if this tree contains data.

    void insert(T const &data);
    // Post: data is stored in this tree in order
    // with no duplicates.

    void remove(T const &data);
    // Post: If data is found, then it is removed
    // from this tree.

    void toStream(ostream &os) const;
    // Post: A string representation of this tree
    // is streamed to os.
};

// ========= Node =========
template<class T>
class Node {
    friend class LLRBTree<T>;

private:
    shared_ptr<Node> _left;
    T _data;
    shared_ptr<Node> _right;
    bool _color; // Color of link from parent.

public:
    explicit Node(T data);
    // Post: This node is allocated with _data set to data, _color
    // set to RED, and _left, _right set to nullptr.

private:
    shared_ptr<Node<T>> fixup(shared_ptr<Node<T>> h);
    // Pre: h->_left and h->_right are roots of left-leaning red-black trees.
    // Post: h is a root of a left-leaning red-black tree.
    // Post: A pointer to the root node of the modified tree is returned.

    void flipColors(shared_ptr<Node<T>> h);
    // Pre: Children of h have the same color.
    // Post: The colors of h and its children are flipped.

    shared_ptr<Node<T>> insert(shared_ptr<Node<T>> h, T const &data);
    // Post: val is stored in root node h in order as a leaf.
    // Post: A pointer to the root node of the modified tree is returned.

    bool isRed(shared_ptr<Node<T>> h);
    // Post: Returns false if h == nullptr.
    // Otherwise returns true if h node is RED.

    T min(shared_ptr<Node<T>> h);
    // Pre: h != nullptr.
    // Post: The minimum of tree rooted at h is returned.

    shared_ptr<Node<T>> moveRedLeft(shared_ptr<Node<T>> h);
    // Pre: Both h->_left and h->_left->_left are BLACK.
    // Post: Either h->_left or one of its children is RED.
    // Post: A pointer to the root node of the modified tree is returned.

    shared_ptr<Node<T>> moveRedRight(shared_ptr<Node<T>> h);
    // Pre: Both h->_right and h->_right->_left are BLACK.
    // Post: Either h->_right or one of its children is RED.
    // Post: A pointer to the root node of the modified tree is returned.

    shared_ptr<Node<T>> remove(shared_ptr<Node<T>> h, T const &data);
    // Post: data is removed from root node h.
    // Post: A pointer to the root node of the modified tree is returned.

    shared_ptr<Node<T>> removeMin(shared_ptr<Node<T>> h);
    // Pre: h != nullptr.
    // Post: The minimum value is removed from root node h.
    // Post: A pointer to the root node of the modified tree is returned.

    shared_ptr<Node<T>> rotateLeft(shared_ptr<Node<T>> h);
    // Pre: h->_right is RED.
    // Post: h is rotated left.
    // Post: A pointer p to the root node of the modified tree is returned.
    // Post: p->left is RED.
    // Unchanged: Color of link to new root from its parent.

    shared_ptr<Node<T>> rotateRight(shared_ptr<Node<T>> h);
    // Pre: h->_left is RED.
    // Post: h is rotated right.
    // Post: A pointer p to the root node of the modified tree is returned.
    // Post: p->right is RED.
    // Unchanged: Color of link to new root from its parent.

    void toStream(shared_ptr<Node<T>> h, string prRight, string prRoot, string prLeft, ostream &os) const;
};

template<class T>
Node<T>::Node(T data) : _color(RED), _data(data) {
}

// ========= contains =========
template<class T>
bool LLRBTree<T>::contains(T const &data) {
    shared_ptr<Node<T>> p = _root;
    while (p) {
        if (p->_data == data)
            return true;
        else if (p->_data < data)
            p = p->_right;
        else
            p = p->_left;
    }
    return false;
}

// ========= fixup =========
template<class T>
shared_ptr<Node<T>> Node<T>::fixup(shared_ptr<Node<T>> h) {
    if (isRed(h->_right)) {
        h = rotateLeft(h);
    }
    if (isRed(h->_left) && isRed(h->_left->_left)) {
        h = rotateRight(h);
    }
    if (isRed(h->_left) && isRed(h->_right)) {
        flipColors(h);
    }
    return h;
}

// ========= flipColors =========
template<class T>
void Node<T>::flipColors(shared_ptr<Node<T>> h) {
    if (isRed(h->_left) != isRed(h->_right)) {
        cerr << "flipColors precondition violated: "
             << "Children of h have different colors." << endl;
        throw -1;
    }
    h->_color = !h->_color;
    h->_left->_color = !h->_left->_color;
    h->_right->_color = !h->_right->_color;
}

// ========= insert =========
template<class T>
void LLRBTree<T>::insert(T const &data) {
    _root = _root->insert(_root, data);
    _root->_color = BLACK;
}

template<class T>
shared_ptr<Node<T>> Node<T>::insert(shared_ptr<Node<T>> h, T const &data) {
    if (h == nullptr) {
        return make_shared<Node<T>>(data);
    }
    if (data < h->_data) {
        h->_left = insert(h->_left, data);
    }
    else if (data > h->_data) {
        h->_right = insert(h->_right, data);
    } // else no duplicates.
    return fixup(h);
}

// ========= isRed =========
template<class T>
bool Node<T>::isRed(shared_ptr<Node<T>> h) {
    return h == nullptr ? BLACK : h->_color;
}

// ========= min =========
template<class T>
T Node<T>::min(shared_ptr<Node<T>> h) {
    auto p = h;
    while (p->_left) {
        p = p->_left;
    }
    return p->_data;
}

// ========= moveRedLeft =========
template<class T>
shared_ptr<Node<T>> Node<T>::moveRedLeft(shared_ptr<Node<T>> h) {
    if (isRed(h->_left) || isRed(h->_left->_left)) {
        cerr << "moveRedLeft precondition violated: h->_left is RED or h->_left->_left is RED" << endl;
        throw -1;
    }
    flipColors(h);
    if (isRed(h->_right->_left)) {
        h->_right = rotateRight(h->_right);
        h = rotateLeft(h);
        flipColors(h);
    }
    return h;
}

// ========= moveRedRight =========
template<class T>
shared_ptr<Node<T>> Node<T>::moveRedRight(shared_ptr<Node<T>> h) {
    if (isRed(h->_right) || isRed(h->_right->_left)) {
        cerr << "moveRedRight precondition violated: h->_right is RED or h->_right->_left is RED" << endl;
        throw -1;
    }
    flipColors(h);
    if (isRed(h->_left->_left)) {
        h = rotateRight(h);
        flipColors(h);
    }
    return h;
}

// ========= operator<< =========
template<class T >
ostream & operator<<(ostream &os, const LLRBTree<T> &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= remove =========
template<class T>
void LLRBTree<T>::remove(T const &data) {
    if (!contains(data)) {
        return;
    }
    _root = _root->remove(_root, data);
    if (_root) {
        _root->_color = BLACK;
    }
}

template<class T>
shared_ptr<Node<T>> Node<T>::remove(shared_ptr<Node<T>> h, T const &data) {
    if (data < h->_data) {
        if (!isRed(h->_left) && !isRed(h->_left->_left)) {
            h = moveRedLeft(h) ;
        }
        h->_left = remove(h->_left, data);
    }
    else {
        if (isRed(h->_left)) {
            h = rotateRight(h);
        }
        if ((data == h->_data) && (h->_right == nullptr)) {
            return nullptr;
        }
        if (!isRed(h->_right) && !isRed(h->_right->_left)) {
            h = moveRedRight(h);
        }
        if (data == h->_data) {
            h->_data = min(h->_right);
            h->_right = removeMin(h->_right);
        }
        else {
            h->_right = remove(h->_right, data);
        }
    }
    return fixup(h);
}

// ========= removeMin =========
template<class T>
shared_ptr<Node<T>> Node<T>::removeMin(shared_ptr<Node<T>> h) {
    if (h == nullptr) {
        cerr << "removeMin precondition violated: "
             << "h == nullptr" << endl;
        throw -1;
    }
    if (h->_left == nullptr) {
        return nullptr;
    }
    if (!isRed(h->_left) && !isRed(h->_left->_left)) {
        h = moveRedLeft(h);
    }
    h->_left = removeMin(h->_left);
    return fixup(h);
}

// ========= rotateLeft =========
template<class T>
shared_ptr<Node<T>> Node<T>::rotateLeft(shared_ptr<Node<T>> h) {
    if (!isRed(h->_right)) {
        cerr << "rotateLeft precondition violated: "
             << "h->_right is not RED" << endl;
        throw -1;
    }
    shared_ptr<Node<T>> p = h->_right;
    h->_right = p->_left;
    p->_left = h;
    p->_color = h->_color;
    h->_color = RED;
    return p;
}

// ========= rotateRight =========
template<class T>
shared_ptr<Node<T>> Node<T>::rotateRight(shared_ptr<Node<T>> h) {
    if (!isRed(h->_left)) {
        cerr << "rotateRight precondition violated: "
             << "h->_left is not RED" << endl;
        throw -1;
    }
    shared_ptr<Node<T>> p = h->_left;
    h->_left = p->_right;
    p->_right = h;
    p->_color = h->_color;
    h->_color = RED;
    return p;
}

// ========= toStream =========
char toChar(bool color) {
    return color ? 'r' : 'b';
}

template<class T>
void LLRBTree<T>::toStream(ostream & os) const {
    if (_root == nullptr) {
        os << "(b)";
    }
    else {
        _root->toStream(_root, "", "", "", os);
    }
}

template<class T>
void Node<T>::toStream(shared_ptr<Node<T>> h, string prRight, string prRoot, string prLeft, ostream & os) const {
    if (h->_right == nullptr) {
        os << prRight << "      -(b)" << endl;
    }
    else {
        toStream(h->_right, prRight + "      ", prRight + "      ", prRight + "     |", os);
    }
    os << prRoot << toChar(h->_color);
    os.fill('-');
    os.width(4);
    os.setf(ios::left, ios::adjustfield);
    os << h->_data << "|" << endl;
    if (h->_left == nullptr) {
        os << prLeft << "      -(b)" << endl;
    }
    else {
        toStream(h->_left, prLeft + "     |", prLeft + "      ", prLeft + "      ", os);
    }
}

#endif
