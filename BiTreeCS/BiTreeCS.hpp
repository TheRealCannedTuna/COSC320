// File: BiTreeCS/BiTreeCS.hpp

#ifndef BiTreeCS_HPP_
#define BiTreeCS_HPP_

#include <iostream> // ostream.
#include <memory>

using namespace std;

template<class T> class AcsNode; // Forward declaration.
template<class T> class NEcsNode; // Forward declaration.
template<class T> class MTcsNode; // Forward declaration.

// ========= BiTreeCS =========
template<class T> class BiTreeCS {
    friend class NEcsNode<T>;
    friend class MTcsNode<T>;
private:
    shared_ptr<AcsNode<T>> _root;

    explicit BiTreeCS(shared_ptr<AcsNode<T>> node);
    // Post: _root points to node with no allocation.

public: // Constructors
    BiTreeCS();
    // Post: This tree is initialized to be empty.

    BiTreeCS(BiTreeCS<T> const &rhs) = delete;
    // copy constructor disabled

public:
    void clear();
    // Post: This tree is cleared to the empty tree.

    bool contains(T const &data) const;
    // Post: true is returned if val is contained in this tree;
    // otherwise, false is returned.

private:
    shared_ptr<AcsNode<T>> copyRoot(BiTreeCS<T> const &rhs);
    // Post: A deep copy of the root of rhs is returned.

public:
    bool equals(BiTreeCS<T> const &rhs) const;
    // Post: true is returned if this tree equals tree rhs;
    // otherwise, false is returned.
    // Two trees are equal if they contain the same number
    // of equal elements with the same shape.

private:
    bool equalsHelper(T const &data, BiTreeCS<T> const &left, BiTreeCS<T> const &right) const;
    // Post: true is returned if root equals this->root(),
    // left equals this->left(), and right equals this->right();
    // otherwise, false is returned.

public:
    int height() const;
    // Post: The height of this tree is returned.

    void inOrder(ostream &os) const;
    // Post: An inorder representation of this tree is sent to os.

    void insertRoot(T const &data);
    // Pre: This tree is empty.
    // Post: This tree has one root node containing data.

    bool isEmpty() const;
    // Post: true is returned if this tree is empty;
    // otherwise, false is returned.

    shared_ptr<BiTreeCS<T>> left();
    shared_ptr<BiTreeCS<T>> const left() const;
    // Pre: This tree is not empty.
    // Post: A shared_ptr to the left child of this tree is returned.

    T const &max() const;
    // Pre: This tree is not empty.  T is totally ordered by operator>.
    // Post: The maximum element of this tree is returned.

    int numLeaves() const;
    // Post: The number of leaves of this tree is returned.

    int numNodes() const;
    // Post: The number of nodes of this tree is returned.

    BiTreeCS &operator=(BiTreeCS<T> const &rhs);
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
    // Post: The root node is removed from this tree and its element is returned.

    shared_ptr<BiTreeCS<T>>  right();
    shared_ptr<BiTreeCS<T>>  const right() const;
    // Pre: This tree is not empty.
    // Post: A shared_ptr to the right child of this tree is returned.

    T &root();
    T const &root() const;
    // Pre: This tree is not empty.
    // Post: A reference to the root element of this tree is returned.

    void setLeftSubTree(shared_ptr<BiTreeCS<T>> newLeft);
    // Pre: This tree is not empty.
    // Post: The left subtree of this tree is replaced by newLeft.

    void setRightSubTree(shared_ptr<BiTreeCS<T>> newRight);
    // Pre: This tree is not empty.
    // Post: The right subtree of this tree is replaced by newRight.

    void toStream(ostream &os) const;
    // Post: A string representation of this tree is sent to os.

private:
    void toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const;
};

// ========= AcsNode =========
template<class T> class AcsNode {
public:
    virtual ~AcsNode() = default;
    // Virtual destructor necessary for subclassing.

    virtual void clear(BiTreeCS<T> &owner) = 0;
    virtual bool contains(T const &data) const = 0;
    virtual shared_ptr<AcsNode<T>> copyRoot() = 0;
    // Post: A deep copy of this node is returned.
    virtual bool equals(BiTreeCS<T> const &rhs) const = 0;
    virtual bool equalsHelper(T const &data, BiTreeCS<T> const &left, BiTreeCS<T> const &right) const = 0;
    virtual int height() const = 0;
    virtual void inOrder(ostream &os) const = 0;
    virtual void insertRoot(BiTreeCS<T> &owner, T const &data) = 0;
    virtual bool isEmpty() const = 0;
    virtual shared_ptr<BiTreeCS<T>> left() = 0;
    virtual shared_ptr<BiTreeCS<T>> const left() const = 0;
    virtual T const &max() const = 0;
    virtual int numLeaves() const = 0;
    virtual int numNodes() const = 0;
    virtual void postOrder(ostream &os) const = 0;
    virtual void preOrder(ostream &os) const = 0;
    virtual void remLeaves(BiTreeCS<T> &owner) = 0;
    virtual T remRoot(BiTreeCS<T> &owner) = 0;
    virtual shared_ptr<BiTreeCS<T>> right() = 0;
    virtual shared_ptr<BiTreeCS<T>> const right() const = 0;
    virtual T &root() = 0;
    virtual T const &root() const = 0;
    virtual void setLeftSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newLeft) = 0;
    virtual void setRightSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newRight) = 0;
    virtual void toStream(ostream &os) const = 0;
    virtual void toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const = 0;
};

// ========= MTcsNode =========
template<class T> class MTcsNode : public AcsNode<T> {
    friend class BiTreeCS<T>;
    friend class NEcsNode<T>;
private:
    MTcsNode() = default;
public:
    MTcsNode(const MTcsNode<T> &rhs)         = delete; // Disabled.
    MTcsNode &operator=(const MTcsNode &rhs) = delete; // Disabled for node.

    void clear(BiTreeCS<T> &owner) override;
    bool contains(T const &data) const override;
    shared_ptr<AcsNode<T>> copyRoot() override;
    bool equals(BiTreeCS<T> const &rhs) const override;
    bool equalsHelper(T const &data, BiTreeCS<T> const &left, BiTreeCS<T> const &right) const override;
    int height() const override;
    void insertRoot(BiTreeCS<T> &owner, T const &data) override;
    void inOrder(ostream &os) const override;
    bool isEmpty() const override;
    shared_ptr<BiTreeCS<T>> left() override;
    shared_ptr<BiTreeCS<T>> const left() const override;
    T const &max() const override;
    int numLeaves() const override;
    int numNodes() const override;
    void postOrder(ostream &os) const override;
    void preOrder(ostream &os) const override;
    void remLeaves(BiTreeCS<T> &owner) override;
    T remRoot(BiTreeCS<T> &owner) override;
    shared_ptr<BiTreeCS<T>> right() override;
    shared_ptr<BiTreeCS<T>> const right() const override;
    T &root() override;
    T const &root() const override;
    void setLeftSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newLeft) override;
    void setRightSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newRight) override;
    void toStream(ostream &os) const override;
    void toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const override;
};

// ========= NEcsNode =========
template<class T> class NEcsNode : public AcsNode<T> {
    friend class BiTreeCS<T>;
    friend class MTcsNode<T>;
private:
    shared_ptr<BiTreeCS<T>> _left;
    T _data;
    shared_ptr<BiTreeCS<T>> _right;

    explicit NEcsNode(T const &data);
    // Post: _data is data.

    NEcsNode(shared_ptr<AcsNode<T>> leftNode, T data, shared_ptr<AcsNode<T>> rightNode);
    // Post: _left->_root and _right->_root point to leftNode and rightNode, and _data is data.

    explicit NEcsNode(shared_ptr<const NEcsNode<T>> rhs);
    // Post: _left is rhs->_left, _data is rhs->_data and _right is rhs->_right->

public:
    NEcsNode(const NEcsNode<T> &rhs)         = delete; // Copy constructor disabled.
    NEcsNode &operator=(const NEcsNode &rhs) = delete; // Disabled for node.

    void clear(BiTreeCS<T> &owner) override;
    bool contains(T const &data) const override;
    shared_ptr<AcsNode<T>> copyRoot() override;
    bool equals(BiTreeCS<T> const &rhs) const override;
    bool equalsHelper(T const &data, BiTreeCS<T> const &left, BiTreeCS<T> const &right) const override;
    int height() const override;
    void inOrder(ostream &os) const override;
    void insertRoot(BiTreeCS<T> &owner, T const &data) override;
    bool isEmpty() const override;
    shared_ptr<BiTreeCS<T>> left() override;
    shared_ptr<BiTreeCS<T>> const left() const override;
    T const &max() const override;
    int numLeaves() const override;
    int numNodes() const override;
    void postOrder(ostream &os) const override;
    void preOrder(ostream &os) const override;
    void remLeaves(BiTreeCS<T> &owner) override;
    T remRoot(BiTreeCS<T> &owner) override;
    shared_ptr<BiTreeCS<T>> right() override;
    shared_ptr<BiTreeCS<T>> const right() const override;
    T &root() override;
    T const &root() const override;
    void setLeftSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newLeft) override;
    void setRightSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newRight) override;
    void toStream(ostream &os) const override;
    void toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const override;
};

// ========= Constructors =========
template<class T>
BiTreeCS<T>::BiTreeCS():
    _root(new MTcsNode<T>()) {
}

template<class T>
BiTreeCS<T>::BiTreeCS(shared_ptr<AcsNode<T>> node):
    _root(node) {
}

template<class T>
NEcsNode<T>::NEcsNode(T const &data):
    _left(make_shared<BiTreeCS<T>>()),
    _data(data),
    _right(make_shared<BiTreeCS<T>>()) {
}

template<class T>
NEcsNode<T>::NEcsNode(shared_ptr<AcsNode<T>> leftNode, T data, shared_ptr<AcsNode<T>> rightNode):
    NEcsNode(data) {
    _left->_root = leftNode;
    _right->_root = rightNode;
}

template<class T>
NEcsNode<T>::NEcsNode(shared_ptr<const NEcsNode<T>> rhs):
    _left(rhs->_left), _data(rhs->_data), _right(rhs->_right) {
}

// ========= clear =========
template<class T>
void BiTreeCS<T>::clear() {
    _root.reset(new MTcsNode<T>);
    // automatic garbage collection does the rest
}

template<class T>
void MTcsNode<T>::clear(BiTreeCS<T> &) {
}

template<class T>
void NEcsNode<T>::clear(BiTreeCS<T> &owner) {
//    cerr << "NEcsNode<T>::clear: Exercise for the student." << endl;
//    throw -1;
}

// ========= contains =========
template<class T>
bool BiTreeCS<T>::contains(T const &data) const {
    return _root->contains(data);
}

template<class T>
bool MTcsNode<T>::contains(T const &data) const {
    return false;
}

template<class T>
bool NEcsNode<T>::contains(T const &data) const {
    if (data == _data) return true;
    return _left->contains(data) || _right->contains(data);
}

// ========= copyRoot =========
template<class T>
shared_ptr<AcsNode<T>> BiTreeCS<T>::copyRoot(BiTreeCS<T> const &rhs) {
    return rhs._root->copyRoot();
}

template<class T>
shared_ptr<AcsNode<T>> MTcsNode<T>::copyRoot() {
    return shared_ptr<MTcsNode<T>>(new MTcsNode<T>());
}

template<class T>
shared_ptr<AcsNode<T>> NEcsNode<T>::copyRoot() {
    return shared_ptr<NEcsNode<T>>(new NEcsNode<T>(_left->_root->copyRoot(),
                                                   _data,
                                                   _right->_root->copyRoot()));
}

// ========= equals =========
template<class T>
bool BiTreeCS<T>::equals(BiTreeCS<T> const &rhs) const {
    return _root->equals(rhs);
}

template<class T>
bool MTcsNode<T>::equals(BiTreeCS<T> const &rhs) const {
    return rhs.isEmpty();
}

template<class T>
bool NEcsNode<T>::equals(BiTreeCS<T> const &rhs) const {
    if (rhs.isEmpty() || _data != rhs.root()) return false;
    if (!_left->isEmpty() && rhs.left()->isEmpty() || _left->isEmpty() && !rhs.left()->isEmpty())
        return false;
    if (!_right->isEmpty() && rhs.right()->isEmpty() || _right->isEmpty() && !rhs.right()->isEmpty())
        return false;
    return _left->equals(*rhs.left()) && _right->equals(*rhs.right());
}

// --------- equalsHelper ---------
template<class T>
bool BiTreeCS<T>::equalsHelper(T const &data, BiTreeCS<T> const &left, BiTreeCS<T> const &right) const {
    cerr << "BiTreeCS<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}

template<class T>
bool MTcsNode<T>::equalsHelper(T const &, BiTreeCS<T> const &, BiTreeCS<T> const &) const {
    cerr << "MTcsNode<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}

template<class T>
bool NEcsNode<T>::equalsHelper(T const &data, BiTreeCS<T> const &left, BiTreeCS<T> const &right) const {
    cerr << "NEcsNode<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}

// ========= height =========
template<class T>
int BiTreeCS<T>::height() const {
    return _root->height();
}

template<class T>
int MTcsNode<T>::height() const {
    return 0;
}

template<class T>
int NEcsNode<T>::height() const {
    return _left->height() > _right->height() ? 1 + _left->height() : 1 + _right->height();
}

// ========= inOrder =========
template<class T>
void BiTreeCS<T>::inOrder(ostream &os) const {
    _root->inOrder(os);
}

template<class T>
void MTcsNode<T>::inOrder(ostream &os) const {
}

template<class T>
void NEcsNode<T>::inOrder(ostream &os) const {
    _left->inOrder(os);
    os << _data << "  ";
    _right->inOrder(os);
}

// ========= insertRoot =========
template<class T>
void BiTreeCS<T>::insertRoot(T const &data) {
    _root->insertRoot(*this, data);
}

template<class T>
void MTcsNode<T>::insertRoot(BiTreeCS<T> &owner, T const &data) {
    owner._root.reset(new NEcsNode<T>(data));
}

template<class T>
void NEcsNode<T>::insertRoot(BiTreeCS<T> &, T const &) {
    cerr << "insertRoot precondition violated: "
         << "Cannot insert root into a non empty tree" << endl;
    throw -1;
}

// ========= isEmpty =========
template<class T>
bool BiTreeCS<T>::isEmpty() const {
    return _root->isEmpty();
}

template<class T>
bool MTcsNode<T>::isEmpty() const {
    return true;
}

template<class T>
bool NEcsNode<T>::isEmpty() const {
    return false;
}

// ========= left =========
template<class T>
shared_ptr<BiTreeCS<T>> BiTreeCS<T>::left() {
    return _root->left();
};

template<class T>
shared_ptr<BiTreeCS<T>> MTcsNode<T>::left() {
    cerr << "left precondition violated: "
         << "An empty tree has has no left subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCS<T>> NEcsNode<T>::left() {
    return _left;
}

// ========= left const =========
template<class T>
shared_ptr<BiTreeCS<T>> const BiTreeCS<T>::left() const {
    return _root->left();
};

template<class T>
shared_ptr<BiTreeCS<T>> const MTcsNode<T>::left() const {
    cerr << "left precondition violated: "
         << "An empty tree has has no left subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCS<T>> const NEcsNode<T>::left() const {
    return _left;
}

// ========= max =========
template<class T>
T const &BiTreeCS<T>::max() const {
    return _root->max();
}

template<class T>
T const &MTcsNode<T>::max() const {
    cerr << "max precondition violated: "
         << "An empty tree has no maximum." << endl;
    throw -1;
}

template<class T>
T const &NEcsNode<T>::max() const {
    T const &leftMax = (_left->isEmpty()) ? _data : _left->max();
    T const &rightMax = (_right->isEmpty()) ? _data : _right->max();
    return (leftMax > rightMax) ?
        ((leftMax > _data) ? leftMax : _data) :
        ((rightMax > _data) ? rightMax: _data);
}

// ========= numLeaves =========
template<class T>
int BiTreeCS<T>::numLeaves() const {
    return _root->numLeaves();
}

template<class T>
int MTcsNode<T>::numLeaves() const {
    return 0;
}

template<class T>
int NEcsNode<T>::numLeaves() const {
    if (_left->isEmpty() && _right->isEmpty()) return 1;
    return _left->numLeaves() + _right->numLeaves();
}

// ========= numNodes =========
template<class T>
int BiTreeCS<T>::numNodes() const {
    return _root->numNodes();
}

template<class T>
int MTcsNode<T>::numNodes() const {
    return 0;
}

template<class T>
int NEcsNode<T>::numNodes() const {
    return 1 + _left->numNodes() + _right->numNodes();
}

// ========= operator= =========
template<class T>
BiTreeCS<T> &BiTreeCS<T>::operator=(BiTreeCS<T> const &rhs) {
    if (this != &rhs) { // In case someone writes myTree = myTree;
        _root = copyRoot(rhs);
    }
    return *this;
}

// ========= operator== =========
template<class T>
bool operator==(BiTreeCS<T> const &lhs, BiTreeCS<T> const &rhs) {
    return lhs.equals(rhs);
}

// ========= operator<< =========
template<class T>
ostream& operator<<(ostream& os, const BiTreeCS<T>& rhs) {
    rhs.toStream(os);
    return os;
}

// ========= postOrder =========
template<class T>
void BiTreeCS<T>::postOrder(ostream &os) const {
    _root->postOrder(os);
}

template<class T>
void MTcsNode<T>::postOrder(ostream &os) const {
}

template<class T>
void NEcsNode<T>::postOrder(ostream &os) const {
    _left->postOrder(os);
    _right->postOrder(os);
    os << _data << "  ";
}

// ========= preOrder =========
template<class T>
void BiTreeCS<T>::preOrder(ostream &os) const {
    _root->preOrder(os);
}

template<class T>
void MTcsNode<T>::preOrder(ostream &os) const {
}

template<class T>
void NEcsNode<T>::preOrder(ostream &os) const {
    os << _data << "  ";
    _left->preOrder(os);
    _right->preOrder(os);
}

// ========= remLeaves =========
template<class T>
void BiTreeCS<T>::remLeaves() {
    _root->remLeaves(*this);
}

template<class T>
void MTcsNode<T>::remLeaves(BiTreeCS<T> &owner) {
}

template<class T>
void NEcsNode<T>::remLeaves(BiTreeCS<T> &owner) {
    if (_left->isEmpty() && _right->isEmpty()) {        // this is a leaf node
        // reset the parent to a new MTcsNode
        owner._root.reset(new MTcsNode<T>);
    } else {
        _left->remLeaves();
        _right->remLeaves();
    }
}

// ========= remRoot =========
template<class T>
T BiTreeCS<T>::remRoot() {
    return _root->remRoot(*this);
}

template<class T>
T MTcsNode<T>::remRoot(BiTreeCS<T> &owner) {
    cerr << "remRoot precondition violated: "
         << "Cannot remove root from an empty tree." << endl;
    throw -1;
}

template<class T>
T NEcsNode<T>::remRoot(BiTreeCS<T> &owner) {
    if(!_left->isEmpty() && !_right->isEmpty()) {
        cerr << "remRoot: there must be an empty child" << endl;
        throw -1;
    }
    auto temp = _left->isEmpty() ? _right->_root : _left->_root;
    owner._root = temp;
    return _data;
}

// ========= right =========
template<class T>
shared_ptr<BiTreeCS<T>>  BiTreeCS<T>::right() {
    return _root->right();
};

template<class T>
shared_ptr<BiTreeCS<T>> MTcsNode<T>::right() {
    cerr << "right precondition violated: "
         << "An empty tree has has no right subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCS<T>> NEcsNode<T>::right() {
    return _right;
}

// ========= right const =========
template<class T>
shared_ptr<BiTreeCS<T>>  const BiTreeCS<T>::right() const {
    return _root->right();
};

template<class T>
shared_ptr<BiTreeCS<T>> const MTcsNode<T>::right() const {
    cerr << "right precondition violated: An empty tree has has no right subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCS<T>> const NEcsNode<T>::right() const {
    return _right;
}

// ========= root =========
template<class T>
T &BiTreeCS<T>::root() {
    return _root->root();
}

template<class T>
T &MTcsNode<T>::root() {
    cerr << "MTcsNode<T>::root: an empty tree has no root." << endl;
    throw -1;
}

template<class T>
T &NEcsNode<T>::root() {
    return _data;
}

// ========= root const =========
template<class T>
T const &BiTreeCS<T>::root() const {
    return _root->root();
}

template<class T>
T const &MTcsNode<T>::root() const {
    cerr << "MTcsNode<T>::root: an empty tree has no root." << endl;
    throw -1;
}

template<class T>
T const &NEcsNode<T>::root() const {
    return _data;
}

// ========= setLeftSubTree =========
template<class T>
void BiTreeCS<T>::setLeftSubTree(shared_ptr<BiTreeCS<T>> newLeft) {
    _root->setLeftSubTree(*this, newLeft);
}

template<class T>
void MTcsNode<T>::setLeftSubTree(BiTreeCS<T>&, shared_ptr<BiTreeCS<T>> ) {
    cerr << "setLeftSubTree precondition violated: "
         << "An empty tree has no left subtree." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::setLeftSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newLeft) {
    _left = newLeft;
}

// ========= setRightSubTree =========
template<class T>
void BiTreeCS<T>::setRightSubTree(shared_ptr<BiTreeCS<T>> newRight) {
    _root->setRightSubTree(*this, newRight);
}

template<class T>
void MTcsNode<T>::setRightSubTree(BiTreeCS<T>&, shared_ptr<BiTreeCS<T>> ) {
    cerr << "setRightSubTree precondition violated: "
         << "An empty tree has no right subtree." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::setRightSubTree(BiTreeCS<T> &owner, shared_ptr<BiTreeCS<T>> newRight) {
    _right = newRight;
}

// ========= toStream =========
template<class T>
void BiTreeCS<T>::toStream(ostream &os) const {
    _root->toStream(os);
}

template<class T>
void MTcsNode<T>::toStream(ostream &os) const {
    os << "*" << endl;
}

template<class T>
void NEcsNode<T>::toStream(ostream &os) const {
    _right->toStreamHelper("     ", "     ", "    |", os);
    os.fill('-');
    os.width(4);
    os.setf(ios::left, ios::adjustfield);
    os << _data << "|" << endl;
    _left->toStreamHelper("    |", "     ", "     ", os);
}

// --------- toStreamHelper ---------
template<class T>
void BiTreeCS<T>::toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const {
    _root->toStreamHelper(prRight, prRoot, prLeft, os);
}

template<class T>
void MTcsNode<T>::toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const {
    os << prRoot << "-*" << endl;
}

template<class T>
void NEcsNode<T>::toStreamHelper(string prRight, string prRoot, string prLeft, ostream &os) const {
    _right->toStreamHelper(prRight + "     ", prRight + "     ", prRight + "    |", os);
    os << prRoot;
    os.fill('-');
    os.width(4);
    os.setf(ios::left, ios::adjustfield);
    os << _data << "|" << endl;
    _left->toStreamHelper(prLeft + "    |", prLeft + "     ", prLeft + "     ", os);
}

#endif
