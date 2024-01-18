// File: BiTreeCSV/BiTCSVtoStreamVerticalVis.hpp

#ifndef BiTCSV_ZtoStreamVerticaltVis_HPP_
#define BiTCSV_ZtoStreamVerticaltVis_HPP_

#include <iostream>
using namespace std;

#include "BiTreeCSV.hpp"

template<class T>
class BiTCSVtoStreamVerticalHelperVis; // forward declaration

// ========= BiTCSVtoStreamVerticalVis =========
/**
 * Algorithm to print a binary tree vertically in the form:

 root
 |_ left subtree
 |_ right subtree

 * For example,
 *
 70
 |_ 40
 |  |_ 10
 |  |  |_ 20
 |  |  |  |_ ()
 |  |  |  |_ ()
 |  |  |_ 30
 |  |     |_ ()
 |  |     |_ ()
 |  |_ 50
 |     |_ ()
 |     |_ 60
 |        |_ ()
 |        |_ ()
 |_ ()

 * @tparam T Data type of the tree elements with overloaded ostream &operator<<(ostream &os, T const &rhs).
 *
 */
template<class T>
class BiTCSVtoStreamVerticalVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    // ========= Constructor =========
    BiTCSVtoStreamVerticalVis(ostream &os): _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is returned.
    void emptyCase(BiTreeCSV<T> &host) {
        _os << "()";
    }

    void nonEmptyCase(BiTreeCSV<T> &host) {
        _os << host.root() << endl;
        BiTCSVtoStreamVerticalHelperVis<T> toStreamHVis(_os);
        toStreamHVis.setPrefix("|  ");
        host.left()->accept(toStreamHVis);
        _os << endl;
        toStreamHVis.setPrefix("   ");
        host.right()->accept(toStreamHVis);
    }

    // ========= visit const =========
    void emptyCase(const BiTreeCSV<T> &host) {
        _os << "()";
    }

    void nonEmptyCase(const BiTreeCSV<T> &host) {
        _os << host.root() << endl;
        BiTCSVtoStreamVerticalHelperVis<T> toStreamHVis(_os);
        toStreamHVis.setPrefix("|  ");
        host.left()->accept(toStreamHVis);
        _os << endl;
        toStreamHVis.setPrefix("   ");
        host.right()->accept(toStreamHVis);
    }
};

// ========= BiTCSVtoStreamVerticalHelperVis =========
template<class T>
class BiTCSVtoStreamVerticalHelperVis : public ABiTreeCSVVis<T> {
    friend class BiTCSVtoStreamVerticalVis<T>;

private:
    ostream &_os; // Input parameter.
    string _prefix; // Input parameter.

    // ========= Constructor =========
    BiTCSVtoStreamVerticalHelperVis(ostream &os): _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is returned, prefixed with "|_" for the root,
    // prefix + "|  " for the left subtree, and prefix + "   " for the right subtree.
    void emptyCase(BiTreeCSV<T> &host) {
        _os << "|_ ()";
    }

    void nonEmptyCase(BiTreeCSV<T> &host) {
        _os << "|_ " << host.root() << endl;
        string pfx = _prefix;
        _os << pfx;
        _prefix = pfx + "|  ";
        host.left()->accept(*this);
        _os << endl;
        _os << pfx;
        _prefix = pfx + "   ";
        host.right()->accept(*this);
    }

    // ========= visit const =========
    void emptyCase(const BiTreeCSV<T> &host) {
        _os << "|_ ()";
    }

    void nonEmptyCase(const BiTreeCSV<T> &host) {
        _os << "|_ " << host.root() << endl;
        string pfx = _prefix;
        _os << pfx;
        _prefix = pfx + "|  ";
        host.left()->accept(*this);
        _os << endl;
        _os << pfx;
        _prefix = pfx + "   ";
        host.right()->accept(*this);
    }

    // ========= setPrefix =========
    void setPrefix(const string &prefix) {
        _prefix = prefix;
    }
};

#endif
