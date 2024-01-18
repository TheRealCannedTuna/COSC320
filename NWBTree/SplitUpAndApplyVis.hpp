// File: NWBTree/SplitUpAndApplyVis.hpp

#ifndef SPLITUPANDAPPLYVIS_HPP_
#define SPLITUPANDAPPLYVIS_HPP_

#include <iostream>
#include <functional>

#include "ANTreeVis.hpp"

using namespace std;

// ========= SplitUpAndApplyVis =========

template<class T>
class SplitUpAndApplyVis : public ANTreeVis<T> {
    int _order; // Input parameter.
    function<void(NTree<T>&)> _cmd; // Input parameter, C++11 function variable.

public:

    // ========= Constructor =========

    SplitUpAndApplyVis(int order, function<void(NTree<T> &) > cmd) :
        _order(order), _cmd(cmd) {
    }

    // ========= Visit =========

    void caseAt(int size, NTree<T> &host) override {
        if (size > _order) {
            host.splitUpAt(size / 2);
            _cmd(host);
        }
        // Do nothing if size <= order.
    }

    void caseAt(int, NTree<T> const &) override {
        cerr << "SplitUpAndApply precondition violated: Cannot split up a const NTree." << endl;
        throw -1;
    }

    // ========= Setter =========

    void setCmd(function<void(NTree<T> &)> cmd) {
        _cmd = cmd;
    }

};

#endif
