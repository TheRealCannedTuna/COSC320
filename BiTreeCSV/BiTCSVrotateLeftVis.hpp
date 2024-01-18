//
// Created by Dung Nguyen on 8/18/21.
//

#ifndef DP4DSPROGRAMS_BiTCSVROTATELEFT_HPP
#define DP4DSPROGRAMS_BiTCSVROTATELEFT_HPP

#include <iostream>
using namespace std;

#include "BiTreeCSV.hpp"

// ========= BiTCSVrotateLeftVis =========
/**
 * Precondition: pre-host is not empty and pre-host right subtree is not empty.
 * Post condition: post-host right subtree is the left subtree of pre-host right subtree.
 *  The result is the pre-host right subtree whose left subtree is the post-host.
 * @tparam T
 */
template<class T>
class BiTCSVrotateLeftVis : public ABiTreeCSVVis<T> {
private:
    shared_ptr<BiTreeCSV<T>> _result;

public:
    void emptyCase(BiTreeCSV<T> &host) override {
        cerr << "BiTCSVrotateLeftVis: Cannot rotate an empty tree." << endl;
        throw -1;
    }
    
    void nonEmptyCase(BiTreeCSV<T> &host) override;
    // Pre: host.right is not empty.
    
    void emptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVrotateLeftVis: Cannot rotate an empty tree." << endl;
        throw -1;
    }
    
    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        cerr << "BiTCSVrotateLeftVis: Cannot rotate a const tree." << endl;
        throw -1;
    }

    shared_ptr<BiTreeCSV<T>> result() {
        return _result;
    }
    
};

template<class T>
void BiTCSVrotateLeftVis<T>::nonEmptyCase(BiTreeCSV<T> &host) {
    auto rightSubTree = host.right();
    host.setRightSubTree(rightSubTree->left());
    rightSubTree->setLeftSubTree(host.shared_from_this());
    _result = rightSubTree;
}

template<class T>
shared_ptr<BiTreeCSV<T>> rotateLeft(BiTreeCSV<T> &tree) {
    BiTCSVrotateLeftVis<T> rotateLeftVis;
    tree.accept(rotateLeftVis);
    return rotateLeftVis.result();
}

#endif //DP4DSPROGRAMS_BiTCSVROTATELEFT_HPP
