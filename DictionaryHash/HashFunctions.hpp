// File: HashFunctions.hpp

#ifndef HASHFUNCTIONS_HPP
#define HASHFUNCTIONS_HPP

#include <string>

typedef CAMetrics<string> CAMetricsStr;

// Signature for a hash function
typedef function<unsigned int(const CAMetricsStr &) > HashFunction;

inline unsigned int bernsteinHash(const CAMetricsStr &key) {
    string str = key.toT();
    cerr << "bernsteinHash: Exercise for the student." << endl;
    throw -1;
}

inline unsigned int knuthHash(const CAMetricsStr &key) {
    string str = key.toT();
    unsigned int result = static_cast<unsigned int> (str.size());
    cerr << "knuthHash: Exercise for the student." << endl;
    throw -1;
}

#endif  /* HASHFUNCTIONS_HPP */

