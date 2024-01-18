// File: NTree/NTreeToStreamVis.hpp

#ifndef NTreeTOSTREAMVIS_HPP_
#define NTreeTOSTREAMVIS_HPP_

#include <iostream>

#include "ANTreeVis.hpp"
#include "NTree.hpp"

using namespace std;

// ========= NTreeToStreamHelperVis =========

template<class T>
class NTreeToStreamHelperVis : public ANTreeVis<T> {
    template<class S> friend class NTreeToStreamVis;

private:
    ostream &_os;
    string _prefix;

public:
    // ========= Constructor =========

    NTreeToStreamHelperVis(ostream &os) : _os(os) {
    }

    // ========= visit =========

    void caseAt(int size, NTree<T>& host) override {
        if (size == 0) {
            _os << "|_ *";
        } else {
            _os << "|_ ";
            // print the root node:
            for (int k = 0; k < size; k++) {
                _os << host.getData(k) << " ";
            }
            _os << endl;
            // print the children trees from 0 to i-1:
            string pfx = _prefix;
            for (int k = 0; k < size; k++) {
                _os << pfx;
                _prefix = pfx + "|  ";
                host.getChild(k)->accept(*this);
                _os << endl;
            }
            // print the rightmost child tree:
            _prefix = pfx + "   ";
            _os << pfx;
            host.getChild(size)->accept(*this);
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        if (size == 0) {
            _os << "|_ *";
        } else {
            _os << "|_ ";
            // print the root node:
            for (int k = 0; k < size; k++) {
                _os << host.getData(k) << " ";
            }
            _os << endl;
            // print the children trees from 0 to i-1:
            string pfx = _prefix;
            for (int k = 0; k < size; k++) {
                _os << pfx;
                _prefix = pfx + "|  ";
                host.getChild(k)->accept(*this);
                _os << endl;
            }
            // print the rightmost child tree:
            _prefix = pfx + "   ";
            _os << pfx;
            host.getChild(size)->accept(*this);
        }
    }
};

// ========= NTreeToStreamVis =========

template<class T>
class NTreeToStreamVis : public ANTreeVis<T> {
private:
    ostream &_os;

public:

    // ========= Constructor =========

    NTreeToStreamVis(ostream &os) : _os(os) {
    }

    // ========= visit =========
    // Pre: This visitor has been accepted by a host tree.
    // Post: A string representation of this tree is sent to os.

    void caseAt(int size, NTree<T> &host) override {
        if (size == 0) {
            _os << "*";
        } else {
            for (int k = 0; k < size; k++) {
                _os << host.getData(k) << " ";
            }
            _os << endl;
            NTreeToStreamHelperVis<T> tshVis(_os);
            for (int k = 0; k < size; k++) {
                tshVis._prefix = "|  ";
                host.getChild(k)->accept(tshVis);
                _os << endl;
            }
            tshVis._prefix = "   ";
            host.getChild(size)->accept(tshVis);
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        if (size == 0) {
            _os << "*";
        } else {
            for (int k = 0; k < size; k++) {
                _os << host.getData(k) << " ";
            }
            _os << endl;
            NTreeToStreamHelperVis<T> tshVis(_os);
            for (int k = 0; k < size; k++) {
                tshVis._prefix = "|  ";
                host.getChild(k)->accept(tshVis);
                _os << endl;
            }
            tshVis._prefix = "   ";
            host.getChild(size)->accept(tshVis);
        }
    }
};

// ========= operator<< =========

template<class T>
ostream &operator<<(ostream &os, NTree<T> const &rhs) {
    NTreeToStreamVis<T> toStreamVis(os);
    rhs.accept(toStreamVis);
    return os;
}

#endif
