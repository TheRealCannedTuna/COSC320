// File:   Counter.hpp

#ifndef COUNTER_HPP
#define COUNTER_HPP

// ========= Counter =========
/**
 * Object used for counting when each count has an associated cost.
 */
class Counter {
private:
    int _delta;  // the associate cost for each count.
    int _count;  // incremented by _delta after each update.

public:
    // Post: _count == 0 && _delta == cost.
    Counter(int cost = 1) :
        _delta(cost),
        _count(0) {
    }

    // Post: _count is returned.
    int getCount() const {
        return _count;
    }

    // Post: _count is increased by _delta.
    void update() {
        _count += _delta;
    }

    // Post: _count == 0.
    void clear() {
        _count = 0;
    }

    // Post: _delta == cost.
    void setDelta(int cost) {
        _delta = cost;
    }
};

#endif
