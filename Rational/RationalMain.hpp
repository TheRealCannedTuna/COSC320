// File: Rational/RationalMain.hpp

#ifndef RationalMain_hpp
#define RationalMain_hpp

class Rational;

void promptLoop(Rational r[], int cap);
// Loop to prompt the user with the top-level main prompt.
// Post: User has selected the quit option.

void makeRational(Rational &r);
// Prompts user for a rational in the form a or a/b.
// Post: r is assigned the prompted rational.

void clearRational(Rational &r);
// Post: r is the rational 0.

void addRational(Rational r[], int cap);
void subtractRational(Rational r[], int cap);
void multiplyRational(Rational r[], int cap);
void divideRational(Rational r[], int cap);
void negateRational(Rational &r);
void displayRational(Rational &r);
void convertToDecimal(Rational &r);
void equalRational(Rational r[], int cap);
void lessThanRational(Rational r[], int cap);

#endif

