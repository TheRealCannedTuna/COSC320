// File: NWBTree/NWBTreeToStreamVis.hpp

#ifndef NWBTreeTOSTREAMVIS_HPP_
#define NWBTreeTOSTREAMVIS_HPP_

#include <iostream>

#include "ANTreeVis.hpp"
#include "NTree.hpp"

using namespace std;

template <class S> class StreamNonEmptyVis; // Forward declaration.

// ========= NWBTreeToStreamHelpVis =========

template<class T>
class NWBTreeToStreamHelpVis : public ANTreeVis<T> {
    template <class S> friend class NWBTreeToStreamVis;

private:
    ostream &_os; // Input parameter.
    string _prefix; // Output result.

public:

    // ========= Constructor =========

    NWBTreeToStreamHelpVis(ostream &os) : _os(os) {
    }

    // ========= visit =========

    void caseAt(int size, NTree<T> &host) override {
        if (size > 0) {
            _os << "|_ ";
            // streams the root node:
            for (int k = 0; k < size; k++) {
                _os << host.getData(k) << " ";
            }
            _os << endl;

            // streams the children trees from 0 to i-1:
            string pfx = _prefix;
            StreamNonEmptyVis<T> pne(*this, _os, pfx);
            for (int k = 0; k < size; k++) {
                _prefix = pfx + "|  ";
                host.getChild(k)->accept(pne);
            }

            // streams the rightmost child tree:
            _os << pfx;
            _prefix = pfx + "   ";
            host.getChild(size)->accept(*this);
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        if (size > 0) {
            _os << "|_ ";
            // streams the root node:
            for (int k = 0; k < size; k++) {
                _os << host.getData(k) << " ";
            }
            _os << endl;

            // streams the children trees from 0 to i-1:
            string pfx = _prefix;
            StreamNonEmptyVis<T> pne(*this, _os, pfx);
            for (int k = 0; k < size; k++) {
                _prefix = pfx + "|  ";
                host.getChild(k)->accept(pne);
            }

            // streams the rightmost child tree:
            _os << pfx;
            _prefix = pfx + "   ";
            host.getChild(size)->accept(*this);
        }
    }
};

// ========= StreamNonEmptyVis =========

template<class T>
class StreamNonEmptyVis : public ANTreeVis<T> {
    NWBTreeToStreamHelpVis<T> &_tsh; // Does not own this pointer.
    ostream& _os; // Input parameter.
    string _pfx; // Input parameter.

public:

    // ========= Constructor =========

    StreamNonEmptyVis(NWBTreeToStreamHelpVis<T> &tsh, ostream& os, string const &pfx)
    : _tsh(tsh), _os(os), _pfx(pfx) {
    }

    ~StreamNonEmptyVis() {
//        _tsh = nullptr;
    }

    // ========= visit =========

    void caseAt(int size, NTree<T> &host) override {
        if (size > 0) {
            _os << _pfx;
            host.accept(_tsh);
            _os << endl;
        }
    }

    // ========= visit const =========

    void caseAt(int size, NTree<T> const &host) override {
        if (size > 0) {
            _os << _pfx;
            host.accept(_tsh);
            _os << endl;
        }
    }

};

// ========= NWBTreeToStreamVis =========
template<class T>
class NWBTreeToStreamVis : public ANTreeVis<T> {
private:
    ostream &_os; // Input parameter.

public:

    // ========= Constructor =========
    NWBTreeToStreamVis(ostream &os) : _os(os) {
    }

    // ========= visit =========
    void caseAt(int size, NTree<T> &host) override {
        switch (size) {
            case 0:
            {
                _os << "*";
                break;
            }
            default:
            {
                // streams the root data:
                for (int k = 0; k < size; k++) {
                    _os << host.getData(k) << " ";
                }
                _os << endl;
                // streams the children trees from 0 to size-1:
                NWBTreeToStreamHelpVis<T> tshVis(_os);
                StreamNonEmptyVis<T> pne(tshVis, _os, "");
                for (int k = 0; k < size; k++) {
                    tshVis._prefix = "|  ";
                    host.getChild(k)->accept(pne);
                }
                // streams the rightmost child tree:
                tshVis._prefix = "   ";
                host.getChild(size)->accept(tshVis);
            }
        }
    }

    // ========= visit const =========
    void caseAt(int size, NTree<T> const &host) override {
        switch (size) {
            case 0:
            {
                _os << "*";
                break;
            }
            default:
            {
                // streams the root data:
                for (int k = 0; k < size; k++) {
                    _os << host.getData(k) << " ";
                }
                _os << endl;
                // streams the children trees from 0 to size-1:
                NWBTreeToStreamHelpVis<T> tshVis(_os);
                StreamNonEmptyVis<T> pne(tshVis, _os, "");
                for (int k = 0; k < size; k++) {
                    tshVis._prefix = "|  ";
                    host.getChild(k)->accept(pne);
                }
                // streams the rightmost child tree:
                tshVis._prefix = "   ";
                host.getChild(size)->accept(tshVis);
            }
        }
    }
};

// Streams a balanced NTree ONLY!

template<class T>
ostream &toNWStream(ostream &os, NTree<T> const &rhs) {
    NWBTreeToStreamVis<T> toStreamVis(os);
    rhs.accept(toStreamVis);
    return os;
}

#endif
