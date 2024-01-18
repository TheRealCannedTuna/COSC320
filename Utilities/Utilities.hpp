// File: Utilities/Utilities.hpp

#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <fstream> // ifstream.
#include <string> // string.
using namespace std;

const double PI = 3.1415926535898;

double promptDoubleGE(const string &prompt, double limit);
// Prompts the user with message prompt, requesting value >= limit.
// Continually prompts with error message when value input is not >= limit.
// Post: Double precision real >= limit is returned.

int promptIntGE(const string &prompt, int limit);

int promptIntBetween(const string &prompt, int lo, int hi);
// Prompts the user with message prompt, requesting value in lo..hi.
// Continually prompts with error message when value input is not in lo..hi.
// Post: Integer value in lo..hi is returned.

void promptFileOpen(ifstream &ifs);
// Prompts the user for a file name and opens it.

int sgn(int i);
// Post: If 0 <= i then 1 is returned, else -1 is returned.

int gcd(int m, int n);
// Pre: 0 <= m, n.
// Post: The greatest common divisor of m and n is returned.

int abs(int i);
// Post: The absolute value of i is returned.

#endif
