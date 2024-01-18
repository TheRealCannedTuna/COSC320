// File: BiTreeCSV/BiTreeCSV.hpp

#ifndef BiTreeCSV_HPP_
#define BiTreeCSV_HPP_

#include <iostream> // ostream.
#include <memory>
using namespace std;

template<class T> class BiTreeCSV;  // Forward declaration.
template<class T> class AcsvNode;   // Forward declaration.
template<class T> class MTcsvNode;  // Forward declaration.
template<class T> class NEcsvNode;  // Forward declaration.

// ==== Represents an abstract visitor to a mutable binary tree. ===
template<class T>
class ABiTreeCSVVis {
public:
    virtual ~ABiTreeCSVVis() = default;
    virtual void emptyCase(BiTreeCSV<T> &host) = 0;
    virtual void nonEmptyCase(BiTreeCSV<T> &host) = 0;
    virtual void emptyCase(BiTreeCSV<T> const &host) = 0; // For const host.
    virtual void nonEmptyCase(BiTreeCSV<T> const &host) = 0; // For const host.
};

// ========= BiTreeCSV =========
template<class T>
class BiTreeCSV : public enable_shared_from_this<BiTreeCSV<T>> {
    friend class MTcsvNode<T>;
    friend class NEcsvNode<T>;
private:
    shared_ptr<AcsvNode<T>> _root;
    
private: // Constructor
    explicit BiTreeCSV(shared_ptr<AcsvNode<T>> node);
    // Pre: node != nullptr.
    // Post: _root points to node with no allocation.
    
public: // Constructors
    BiTreeCSV();
    // Post: An empty binary tree BiTreeCSV is created.
    
    BiTreeCSV(BiTreeCSV<T> const &rhs) = delete;
    // Copy constructor disabled.
    
public:
    void accept(ABiTreeCSVVis<T> &visitor);
    void accept(ABiTreeCSVVis<T> &visitor) const;
    
private:
    shared_ptr<AcsvNode<T>> copyRoot(BiTreeCSV<T> const &rhs);
    // Post: A deep copy of the root of rhs is returned.
    
public:
    void insertRoot(T const &data);
    // Pre: This tree is empty.
    // Post: This tree has one root node containing data.
    
    shared_ptr<BiTreeCSV<T>> left();
    shared_ptr<BiTreeCSV<T>> const left() const;
    // Pre: This tree is not empty.
    // Post: A shared_ptr to the left child of this tree is returned.
    
private:
    T leftRemRoot(BiTreeCSV<T> &parent);
    // Pre: Parent has at least one empty subtree.
    // Post: The root of parent is removed and returned.
    // Helper for remRoot.
    
public:
    BiTreeCSV &operator=(BiTreeCSV const &rhs);
    // Post: A deep copy of rhs is returned.
    
    T remRoot();
    // Pre: This tree is not empty.
    // Pre: The root of this tree has at least one empty child.
    // Post: The root node is removed from this tree and its element is returned.
    
    shared_ptr<BiTreeCSV<T>> right();
    shared_ptr<BiTreeCSV<T>> const right() const;
    // Pre: This tree is not empty.
    // Post: A shared_ptr to the right child of this tree is returned.
    
private:
    T rightRemRoot(BiTreeCSV<T> &parent);
    // Pre: The left subtree of parent is not empty.
    // Pre: The right subtree of parent is empty.
    // Post: The root of parent is removed and returned.
    // Helper for remRoot.
    
public:
    T &root();
    T const &root() const;
    // Pre: This tree is not empty.
    // Post: A reference to the root element of this tree is returned.
    
    void setLeftSubTree(shared_ptr<BiTreeCSV<T>> newLeft);
    // Pre: This tree is not empty.
    // Post: The left subtree of this tree is replaced by newLeft.
    
    void setRightSubTree(shared_ptr<BiTreeCSV<T>> newRight);
    // Pre: This tree is not empty.
    // Post: The right subtree of this tree is replaced by newRight.
};

// ========= AcsvNode =========
template<class T>
class AcsvNode {
public:
    virtual ~AcsvNode() = default;
    
    virtual void accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) = 0;
    virtual void accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) = 0;
    virtual shared_ptr<AcsvNode<T>> copyRoot() = 0;
    // Post: A deep copy of this node is returned.
    virtual void insertRoot(BiTreeCSV<T> &owner, T const &data) = 0;
    virtual shared_ptr<BiTreeCSV<T>> left() = 0;
    virtual shared_ptr<BiTreeCSV<T>> const left() const = 0;
    virtual T leftRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) = 0;
    virtual T remRoot(BiTreeCSV<T> &owner) = 0;
    virtual shared_ptr<BiTreeCSV<T>> right() = 0;
    virtual shared_ptr<BiTreeCSV<T>> const right() const = 0;
    virtual T rightRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) = 0;
    virtual T &root() = 0;
    virtual T const &root() const = 0;
    virtual void setLeftSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newLeft) = 0;
    virtual void setRightSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newRight) = 0;
};

// ========= MTcsvNode =========
template<class T>
class MTcsvNode : public AcsvNode<T> {
    friend class BiTreeCSV<T>;
    friend class NEcsvNode<T>;
    
private: // Constructor
    MTcsvNode() = default;
    
public: //Constructors
    MTcsvNode(MTcsvNode<T> const &rhs) = delete; // Disabled.
    MTcsvNode &operator=(MTcsvNode const &rhs) = delete; // Disabled.
    
public:
    void accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) override;
    void accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) override;
    shared_ptr<AcsvNode<T>> copyRoot() override;
    void insertRoot(BiTreeCSV<T> &owner, T const &data) override;
    shared_ptr<BiTreeCSV<T>> left() override;
    shared_ptr<BiTreeCSV<T>> const left() const override;
    T leftRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) override;
    T remRoot(BiTreeCSV<T> &owner) override;
    shared_ptr<BiTreeCSV<T>> right() override;
    shared_ptr<BiTreeCSV<T>> const right() const override;
    T rightRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) override;
    T &root() override;
    T const &root() const override;
    void setLeftSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newLeft) override;
    void setRightSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newRight) override;
};

// ========= NEcsvNode =========
template<class T>
class NEcsvNode : public AcsvNode<T> {
    friend class MTcsvNode<T>;
    
private:
    shared_ptr<BiTreeCSV<T>> _left;
    T _data;
    shared_ptr<BiTreeCSV<T>> _right;
    
private: // Constructors
    explicit NEcsvNode(T data);
    // Post: _data is data.
    
    NEcsvNode(shared_ptr<AcsvNode<T>> leftNode, T data, shared_ptr<AcsvNode<T>> rightNode);
    // Pre: leftNode and rightNode are not nullptr.
    // Post: _data is data, _left._root points to leftNode,
    // and _right._root points to rightNode.
    
    explicit NEcsvNode(shared_ptr<const NEcsvNode<T>> rhs);
    // Pre: rhs != nullptr.
    // Post: _data is rhs->_data, _left is rhs->_left, and _right is rhs->_right.
    
public:
    void accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) override;
    void accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) override;
    shared_ptr<AcsvNode<T>> copyRoot() override;
    void insertRoot(BiTreeCSV<T> &owner, T const &data) override;
    shared_ptr<BiTreeCSV<T>> left() override;
    shared_ptr<BiTreeCSV<T>> const left() const override;
    T leftRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) override;
    NEcsvNode &operator=(NEcsvNode const &rhs) = delete; // Disabled.
    T remRoot(BiTreeCSV<T> &owner) override;
    shared_ptr<BiTreeCSV<T>> right() override;
    shared_ptr<BiTreeCSV<T>> const right() const override;
    T rightRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) override;
    T &root() override;
    T const &root() const override;
    void setLeftSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newLeft) override;
    void setRightSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newRight) override;
};

// ========= Constructors =========
template<class T>
BiTreeCSV<T>::BiTreeCSV():
    _root(new MTcsvNode<T>) {
}

template<class T>
BiTreeCSV<T>::BiTreeCSV(shared_ptr<AcsvNode<T>> node):
    _root(node) {
}

template<class T>
NEcsvNode<T>::NEcsvNode(T data):
    _left(new BiTreeCSV<T>()),
                                _data(data),
                                _right(new BiTreeCSV<T>()) {
}

template<class T>
NEcsvNode<T>::NEcsvNode(shared_ptr<AcsvNode<T>> leftNode, T data, shared_ptr<AcsvNode<T>> rightNode):
    NEcsvNode(data) {
    _left->_root = leftNode;
    _right->_root = rightNode;
}

template<class T>
NEcsvNode<T>::NEcsvNode(shared_ptr<const NEcsvNode<T>> rhs):
    _left(rhs->_left),
                                                            _data(rhs->_data),
                                                            _right(rhs->_right) {
}

// ========= accept =========
template<class T>
void BiTreeCSV<T>::accept(ABiTreeCSVVis<T> &visitor) {
    _root->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= accept const =========
template<class T>
void BiTreeCSV<T>::accept(ABiTreeCSVVis<T> &visitor) const {
    _root->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= copyRoot =========
template<class T>
shared_ptr<AcsvNode<T>> BiTreeCSV<T>::copyRoot(BiTreeCSV<T> const &rhs) {
    return rhs._root->copyRoot();
}

template<class T>
shared_ptr<AcsvNode<T>> MTcsvNode<T>::copyRoot() {
    return shared_ptr<MTcsvNode<T>>(new MTcsvNode<T>);
}

template<class T>
shared_ptr<AcsvNode<T>> NEcsvNode<T>::copyRoot() {
    return shared_ptr<NEcsvNode<T>>(new NEcsvNode<T>(_left->_root->copyRoot(),
                                                     _data,
                                                     _right->_root->copyRoot()));
}

// ========= insertRoot =========
template<class T>
void BiTreeCSV<T>::insertRoot(T const &data) {
    _root->insertRoot(*this, data);
}

template<class T>
void MTcsvNode<T>::insertRoot(BiTreeCSV<T> &owner, T const &data) {
    owner._root.reset(new NEcsvNode<T>(data));
}

template<class T>
void NEcsvNode<T>::insertRoot(BiTreeCSV<T> &owner, T const &data) {
    cerr << "insertRoot precondition violated: "
         << "Cannot insert root into a non empty tree" << endl;
    throw -1;
}

// ========= left =========
template<class T>
shared_ptr<BiTreeCSV<T>> BiTreeCSV<T>::left() {
    return _root->left();
}

template<class T>
shared_ptr<BiTreeCSV<T>> MTcsvNode<T>::left() {
    cerr << "left precondition violated: "
         << "An empty tree has no left subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCSV<T>> NEcsvNode<T>::left() {
    return _left;
}

// ========= left const =========
template<class T>
shared_ptr<BiTreeCSV<T>> const BiTreeCSV<T>::left() const {
    return _root->left();
}

template<class T>
shared_ptr<BiTreeCSV<T>> const MTcsvNode<T>::left() const {
    cerr << "left precondition violated: "
         << "An empty tree has no left subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCSV<T>> const NEcsvNode<T>::left() const {
    return _left;
}

// ========= leftRemRoot =========
template<class T>
T BiTreeCSV<T>::leftRemRoot(BiTreeCSV<T> &parent) {
    return _root->leftRemRoot(*this, parent);
}

template<class T>
T MTcsvNode<T>::leftRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) {
    auto temp = parent.root();
    parent._root = parent.right()->_root;
    return temp;
}

template<class T>
T NEcsvNode<T>::leftRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) {
    return parent.right()->rightRemRoot(parent);
}

// ========= operator= =========
template<class T>
BiTreeCSV<T> &BiTreeCSV<T>::operator=(BiTreeCSV const &rhs) {
    if (this != &rhs) { // In case someone writes myTree = myTree;
        _root = copyRoot(rhs);
    }
    return *this;
}

// ========= remRoot =========
template<class T>
T BiTreeCSV<T>::remRoot() {
    return _root->remRoot(*this);
}

template<class T>
T MTcsvNode<T>::remRoot(BiTreeCSV<T> &owner) {
    cerr << "remRoot precondition violated: "
         << "Cannot remove root from an empty tree." << endl;
    throw -1;
}

template<class T>
T NEcsvNode<T>::remRoot(BiTreeCSV<T> &owner) {
    // owner is parent tree of _left.
    return _left->leftRemRoot(owner);
}

// ========= right =========
template<class T>
shared_ptr<BiTreeCSV<T>> BiTreeCSV<T>::right() {
    return _root->right();
}

template<class T>
shared_ptr<BiTreeCSV<T>> MTcsvNode<T>::right() {
    cerr << "right precondition violated: "
         << "An empty tree has no right subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCSV<T>> NEcsvNode<T>::right() {
    return _right;
}

// ========= right const =========
template<class T>
shared_ptr<BiTreeCSV<T>> const BiTreeCSV<T>::right() const {
    return _root->right();
}

template<class T>
shared_ptr<BiTreeCSV<T>> const MTcsvNode<T>::right() const {
    cerr << "right precondition violated: "
         << "An empty tree has no right subtree." << endl;
    throw -1;
}

template<class T>
shared_ptr<BiTreeCSV<T>> const NEcsvNode<T>::right() const {
    return _right;
}

// ========= rightRemRoot =========
template<class T>
T BiTreeCSV<T>::rightRemRoot(BiTreeCSV<T> &parent) {
    return _root->rightRemRoot(*this, parent);
}

template<class T>
T MTcsvNode<T>::rightRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) {
    auto temp = parent.root();
    parent._root = parent.left()->_root;
    return temp;
}

template<class T>
T NEcsvNode<T>::rightRemRoot(BiTreeCSV<T> &owner, BiTreeCSV<T> &parent) {
    // Pre: The left subtree of parent is not empty.
    // Pre: The right subtree of parent is empty.
    // Post: The root of parent is removed and returned.
    // Helper for remRoot.

    auto temp = parent.root();
    parent._root = parent.left()->_root;
    return temp;
}

// ========= root =========
template<class T>
T &BiTreeCSV<T>::root() {
    return _root->root();
}

template<class T>
T &MTcsvNode<T>::root() {
    cerr << "MTcsvNode<T>::root: there is no root lmao." << endl;
    throw -1;
}

template<class T>
T &NEcsvNode<T>::root() {
    return _data;
}

// ========= root const =========
template<class T>
T const &BiTreeCSV<T>::root() const {
    return _root->root();
}

template<class T>
T const &MTcsvNode<T>::root() const {
    cerr << "MTcsvNode<T>::root: there is no root lmao." << endl;
    throw -1;
}

template<class T>
T const &NEcsvNode<T>::root() const {
    return _data;
}

// ========= setLeftSubTree =========
template<class T>
void BiTreeCSV<T>::setLeftSubTree(shared_ptr<BiTreeCSV<T>> newLeft) {
    _root->setLeftSubTree(*this, newLeft);
}

template<class T>
void MTcsvNode<T>::setLeftSubTree(BiTreeCSV<T>& , shared_ptr<BiTreeCSV<T>> ) {
    cerr << "Precondition violated: An empty tree has no left subtree." << endl;
    throw -1;
}

template<class T>
void NEcsvNode<T>::setLeftSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newLeft) {
    _left = newLeft;
}

// ========= setRightSubTree =========
template<class T>
void BiTreeCSV<T>::setRightSubTree(shared_ptr<BiTreeCSV<T>> newRight) {
    _root->setRightSubTree(*this, newRight);
}

template<class T>
void MTcsvNode<T>::setRightSubTree(BiTreeCSV<T>& , shared_ptr<BiTreeCSV<T>> ) {
    cerr << "Precondition violated: An empty tree has no right subtree." << endl;
    throw -1;
}

template<class T>
void NEcsvNode<T>::setRightSubTree(BiTreeCSV<T> &owner, shared_ptr<BiTreeCSV<T>> newRight) {
    _right = newRight;
}

#endif
