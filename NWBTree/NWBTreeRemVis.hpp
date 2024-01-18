// File: NWBTree/NWBTreeRemVis.hpp

#ifndef NWBTreeREMVIS_HPP_
#define NWBTreeREMVIS_HPP_

#include <iostream>
#include <functional>

#include "ANTreeVis.hpp"
#include "SplitUpAndApplyVis.hpp"

using namespace std;

template<class T> class NWBTreeRemHelpVis; // Forward declaration.

// ========= NWBTreeRemVis =========
template<class T>
class NWBTreeRemVis : public ANTreeVis<T> {
private:
    int _order; // Input parameter.
    T _key; // Input parameter.
public:
    // ========= Constructor =========
    NWBTreeRemVis(int order, int key) : _order(order), _key(key) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
            case 0:
            {
                // There is nothing to remove.
                return;
            }
            case 1:
            { // One-element tree node has two children trees.
                // Collapses with the two children trees.
                collapseWithChildren(host);
                // Now falls through to the default case.
            }
            default:
            {
                NWBTreeRemHelpVis<T> rhv(_key, _order, [](NTree<T>&) {}); // C++ 11
                host.accept(rhv);
            }
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        cerr << "Cannot remove elements from a Const NTree." << endl;
        throw -1;
    }
};

// ========= collapseWithChildren =========
// Collapse a one-element node with its two children.

template<class T>
void collapseWithChildren(NTree<T>& tree) {
    tree.spliceAt(1, *(tree.getChild(1)));
    tree.spliceAt(0, *(tree.getChild(0)));
}

// ========= NWBTreeRemHelpVis =========
template<class T>
class NWBTreeRemHelpVis : public ANTreeVis<T> {
private:
    T _key;
    function<void(NTree<T>&)> _cmd; // C++11
    SplitUpAndApplyVis<T> _splitUpAndApply;

public:

    // ========= Constructor =========

    // Initialize _key to key.
    // Initialize _cmd to cmd.
    // Initialize _splitUpAndApply visitor attribute with order and cmd.
    NWBTreeRemHelpVis(T key, int order, function<void(NTree<T>&) > cmd) :
        _key(key), _cmd(cmd), _splitUpAndApply(order, cmd) {
    }
    
    // ========= visit =========

    void caseAt(int size, NTree<T>& host) override {
        switch (size) {
            case 0:
            {
                // Nothing to remove.
                return;
            }
            case 1:
            { // One-element tree node.
                if (host.getData(0) == _key) {
                    host.splitDownAt(0); // Remove the key. Becomes empty.
                }
                else { // Key is not in the tree.
                    _cmd(host); // Splice back to the parent tree.
                }
                return;
            }
            default:
            {
                // Find the index of the candidate data element in the node
                // to split down.
                // If the key is in the node, then the candidate
                // data element is the key itself.
                // Otherwise, the key, if it exists in the tree,
                // must in the right child tree of largest data
                // element that is smaller than the key.
                int k = 0;
                while (k < size && host.getData(k) < _key) {
                    k++;
                }
                if (k == size) { // Key is in the rightmost child tree.
                    k = size - 1;
                }
                host.splitDownAt(k);
                collapseWithChildren(*(host.getChild(k)));
                auto oldCmd = _cmd;
                _cmd = [&host, k](NTree<T>& tree) { // Using C++11 closure.
                    host.spliceAt(k, tree);
                };
                _splitUpAndApply.setCmd(_cmd);
                host.getChild(k)->accept(*this);
                _cmd = oldCmd;
                _splitUpAndApply.setCmd(oldCmd);
                host.accept(_splitUpAndApply);
            }
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        cerr << "Cannot insert into a Const NTree." << endl;
        throw -1;
    }
};

// Global function for convenience

template<class T>
void remove(NTree<T> &tree, int order, int key) {
    NWBTreeRemVis<T> removeVis(order, key);
    tree.accept(removeVis);
}

#endif
