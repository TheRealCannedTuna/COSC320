// File: Utilities/Utilities.cpp

#include <iostream>  // cin, cout, endl, istream, ostream, ifstream.
#include "Utilities.hpp"
using namespace std;

double promptDoubleGE(string const &prompt, double limit) {
    double d;
    cout << prompt << " (>= " << limit << "): ";
    cin >> d;
    while (d < limit) {
        cout << "Must be greater than or equal to " << limit << "." << endl;
        cout << prompt << "(>= " << limit << "): ";
        cin >> d;
    }
    return d;
}

int promptIntGE(string const &prompt, int limit) {
    int i;
    cout << prompt << " (>= " << limit << "): ";
    cin >> i;
    while (i < limit) {
        cout << "Must be greater than or equal to " << limit << "." << endl;
        cout << prompt << "(>= " << limit << "): ";
        cin >> i;
    }
    return i;
}

int promptIntBetween(string const &prompt, int lo, int hi) {
    int i;
    cout << prompt << " (" << lo << ".." << hi << "): ";
    cin >> i;
    while (i < lo || i > hi) {
        cout << "Must be between " << lo << " and " << hi << "." << endl;
        cout << prompt << " (" << lo << ".." << hi << "): ";
        cin >> i;
    }
    return i;
}

void promptFileOpen(ifstream &ifs) {
    string inFileName;
    cout << "File Name? ";
    cin >> inFileName;
    ifs.open(inFileName.c_str(), ios::in);
    if (!ifs) {
        cout << "Cannot open " << inFileName << '.' << endl;
    }
}

int sgn(int i) {
    return (0 <= i ? 1 : -1);
}

int gcd(int m, int n) {
    if (0 == n) {
        return m;
    } else {
        return gcd(n, m % n);
    }
}

int abs(int i) {
    return (0 <= i ? i : -i);
}
