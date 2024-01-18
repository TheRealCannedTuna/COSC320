// File: Rational/RationalMain.cpp

#include <iostream>
#include <cstdlib> // EXIT_SUCCESS
#include <cctype> // toupper.
#include "Rational.hpp"
#include "Utilities.hpp" // promptIntBetween, promptDoubleGE.
#include "RationalMain.hpp"
using namespace std;

int main() {
    const int CAP = 5;
    Rational rats[CAP];
    promptLoop(rats, CAP);
    return EXIT_SUCCESS;
}

void promptLoop(Rational r[], int cap) {
    char response;
    do {
        cout << "\nThere are [0.." << cap - 1 << "] rationals." << endl;
        cout << "(m)ake    (c)lear    (a)dd      (s)ubtract  m(u)ltiply   "
             << "(d)ivide\n"
             << "(n)egate  dis(p)lay  dec(i)mal  (e)quals    (l)ess than  "
             << "(q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'M':
            makeRational(r[promptIntBetween("Which rational?", 0, cap - 1)]);
            break;
        case 'C':
            clearRational(r[promptIntBetween("Which rational?", 0, cap - 1)]);
            break;
        case 'A':
            addRational(r, cap);
            break;
        case 'S':
            subtractRational(r, cap);
            break;
        case 'U':
            multiplyRational(r, cap);
            break;
        case 'D':
            divideRational(r, cap);
            break;
        case 'N':
            negateRational(r[promptIntBetween("Which rational?", 0, cap - 1)]);
            break;
        case 'P':
            cout << "\n";
            displayRational(r[promptIntBetween("Which rational?", 0, cap - 1)]);
            break;
        case 'I':
            convertToDecimal(r[promptIntBetween("Which rational?", 0, cap - 1)]);
            break;
        case 'E':
            equalRational(r, cap);
            break;
        case 'L':
            lessThanRational(r, cap);
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
}

void makeRational(Rational &r) {
    cout << "Enter a rational(a or a/b): ";
    cin >> r;
}

void clearRational(Rational &r) {
    r = 0;
}

void addRational(Rational r[], int cap) {
    int left = promptIntBetween("Left operand?", 0, cap - 1);
    int right = promptIntBetween("Right operand?", 0, cap - 1);
    int result = promptIntBetween("Result operand?", 0, cap - 1);
    r[result] = r[left] + r[right];
}

void subtractRational(Rational r[], int cap) {
    int left = promptIntBetween("Left operand?", 0, cap - 1);
    int right = promptIntBetween("Right operand?", 0, cap - 1);
    int result = promptIntBetween("Result operand?", 0, cap - 1);
    r[result] = r[left] - r[right];
}

void multiplyRational(Rational r[], int cap) {
    int left = promptIntBetween("Left operand?", 0, cap - 1);
    int right = promptIntBetween("Right operand?", 0, cap - 1);
    int result = promptIntBetween("Result operand?", 0, cap - 1);
    r[result] = r[left] * r[right];
}

void divideRational(Rational r[], int cap) {
    int left = promptIntBetween("Left operand?", 0, cap - 1);
    int right = promptIntBetween("Right operand?", 0, cap - 1);
    int result = promptIntBetween("Result operand?", 0, cap - 1);
    r[result] = r[left] / r[right];
}

void negateRational(Rational &r) {
    r = -r;
}

void displayRational(Rational &r) {
    cout << "\n" << r << endl;
}

void convertToDecimal(Rational &r) {
    cout << "\n" << r.toDouble() << endl;
}

void equalRational(Rational r[], int cap) {
    int left = promptIntBetween("Left operand?", 0, cap - 1);
    int right = promptIntBetween("Right operand?", 0, cap - 1);
    cout << "\n" << r[left] << " == " << r[right] << ": "
         << (r[left] == r[right] ? "true" : "false") << endl;
}

void lessThanRational(Rational r[], int cap) {
    int left = promptIntBetween("Left operand?", 0, cap - 1);
    int right = promptIntBetween("Right operand?", 0, cap - 1);
    cout << "\n" << r[left] << " < " << r[right] << ": "
         << (r[left] < r[right] ? "true" : "false") << endl;
}
