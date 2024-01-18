// File: BiTreeCSV/BiTCSVtoStreamVis.hpp

#ifndef BiTCSV_ZTOSTREAMVIS_HPP_
#define BiTCSV_ZTOSTREAMVIS_HPP_

template<class T> class BiTCSV_ZtoStreamHelperVis; // Forward reference.

#include <iostream>
using namespace std;

#include "BiTreeCSV.hpp"

// ========= BiTCSVtoStreamVis =========
/**
 * Algorithm to print a binary tree "sideways", in the form:

 _ right subtree
 |
 root --
 |_ left subtree

 * For example,

 -*
 70--|
 |               -*
 |          60--|
 |         |     -*
 |     50--|
 |    |     -*
 40--|
 |          -*
 |     30--|
 |    |     -*
 10--|
 |     -*
 20--|
 -*

 * @tparam T Data type of the tree elements with overloaded ostream &operator<<(ostream &os, T const &rhs).
 *
 */
template<class T>
class BiTCSVtoStreamVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.

public:
    // ========= Constructor =========
    BiTCSVtoStreamVis(ostream &os):
        _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is sent to os.
    void emptyCase(BiTreeCSV<T> &host) override {
        _os << "*";
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisR
            ("     ", "     ", "    |", _os);
        host.right()->accept(toStreamHelperVisR);
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisL
            ("    |", "     ", "     ", _os);
        host.left()->accept(toStreamHelperVisL);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _os << "*";
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisR
            ("     ", "     ", "    |", _os);
        host.right()->accept(toStreamHelperVisR);
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisL
            ("    |", "     ", "     ", _os);
        host.left()->accept(toStreamHelperVisL);
    }
};

// ========= BiTCSV_ZtoStreamHelperVis =========
template<class T>
class BiTCSV_ZtoStreamHelperVis : public ABiTreeCSVVis<T> {
private:
    ostream &_os; // Input parameter.
    string _prRight; // Input parameter.
    string _prRoot; // Input parameter.
    string _prLeft; // Input parameter.

public:
    // ========= Constructor =========
    BiTCSV_ZtoStreamHelperVis(string prRight, string prRoot, string prLeft, ostream &os):
        _os(os),
        _prRight(prRight),
        _prRoot(prRoot),
        _prLeft(prLeft) {
    }

    // ========= visit =========
    void emptyCase(BiTreeCSV<T> &host) override {
        _os << _prRoot << "-*" << endl;
    }

    void nonEmptyCase(BiTreeCSV<T> &host) override {
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisR
            (_prRight + "     ", _prRight + "     ", _prRight + "    |", _os);
        host.right()->accept(toStreamHelperVisR);
        _os << _prRoot;
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisL
            (_prLeft + "    |", _prLeft + "     ", _prLeft + "     ", _os);
        host.left()->accept(toStreamHelperVisL);
    }

    // ========= visit const =========
    void emptyCase(BiTreeCSV<T> const &host) override {
        _os << _prRoot << "-*" << endl;
    }

    void nonEmptyCase(BiTreeCSV<T> const &host) override {
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisR
            (_prRight + "     ", _prRight + "     ", _prRight + "    |", _os);
        host.right()->accept(toStreamHelperVisR);
        _os << _prRoot;
        _os.fill('-');
        _os.width(4);
        _os.setf(ios::left, ios::adjustfield);
        _os << host.root() << "|" << endl;
        BiTCSV_ZtoStreamHelperVis<T> toStreamHelperVisL
            (_prLeft + "    |", _prLeft + "     ", _prLeft + "     ", _os);
        host.left()->accept(toStreamHelperVisL);
    }
};

// ========= operator<< =========
template<class T>
ostream &operator<< (ostream &os, BiTreeCSV<T> const &tree) {
    BiTCSVtoStreamVis<T> toStreamVis(os);
    tree.accept(toStreamVis);
    return os;
}

#endif
