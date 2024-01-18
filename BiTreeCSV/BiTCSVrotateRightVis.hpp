//
// Created by Dung Nguyen on 8/19/21.
//

#ifndef DP4DSPROGRAMS_BiTCSVROTATERIGHTVIS_HPP
#define DP4DSPROGRAMS_BiTCSVROTATERIGHTVIS_HPP

#include <iostream>
using namespace std;

#include "BiTreeCSV.hpp"

// ========= BiTCSVrotateRightVis =========
/**
 * Precondition: pre-host is not empty and pre-host left subtree is not empty.
 * Post condition: post-host left subtree is the right subtree of pre-host left subtree.
 *  The result is the pre-host left subtree whose right subtree is the post-host.
 * @tparam T
 */
template<class T>
class BiTCSVrotateRightVis : public ABiTreeCSVVis<T> {
private:
    shared_ptr<BiTreeCSV<T>> _result;

public:
    void emptyCase(BiTreeCSV<T> &host) override {
        cerr << "BiTCSVrotateRightVis: Cannot rotate an empty tree." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override;
    // Pre: host.right is not empty.

    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVrotateRightVis: Cannot rotate an empty tree." << endl;
        throw -1;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVrotateRightVis: Cannot rotate a const tree." << endl;
        throw -1;
    }

    shared_ptr<BiTreeCSV<T>> result() {
        return _result;
    }

};

template<class T>
void BiTCSVrotateRightVis<T>::nonEmptyCase(BiTreeCSV<T> &host) {
    auto leftSubTree = host.left();
    host.setLeftSubTree(leftSubTree->right());
    leftSubTree->setRightSubTree(host.shared_from_this());
    _result = leftSubTree;
}

template<class T>
shared_ptr<BiTreeCSV<T>> rotateRight(BiTreeCSV<T> &tree) {
    BiTCSVrotateRightVis<T> rotateRightVis;
    tree.accept(rotateRightVis);
    return rotateRightVis.result();
}

#endif //DP4DSPROGRAMS_BiTCSVROTATERIGHTVIS_HPP
