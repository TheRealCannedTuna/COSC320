// File: HashFunctions.hpp

#ifndef HASHFUNCTIONS_HPP
#define HASHFUNCTIONS_HPP

#include "CAMetrics.hpp"
typedef CAMetrics<string> CAMetricsStr;
typedef function<unsigned int(CAMetricsStr const &)> HashFunction;

inline unsigned int bernsteinHash(CAMetricsStr const &x) {
    string str = x.toT();
    unsigned int result = static_cast<unsigned int> (5381);
    for (char i : str) {
        result = (result << 5) + result + i;
    }
    return result;
}

inline unsigned int knuthHash(CAMetricsStr const &x) {
    string str = x.toT();
    unsigned int result = static_cast<unsigned int> (str.size());
    for (char i : str) {
        result = (result << 5 | result >> (32 - 5)) ^ i;
    }
    return result;
}

#endif  /* HASHFUNCTIONS_HPP */

