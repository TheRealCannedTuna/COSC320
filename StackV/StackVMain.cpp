// File: StackA/StackAMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "StackV.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    shared_ptr<AStack<double>>
        stackV = make_shared<StackV<double>>(promptIntGE("Stack capacity", 1));
    double value;
    char response;
    do {
        cout << "\n(e)mpty  (f)ull  (p)ush  p(o)p  (t)op  (w)rite  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'E':
            if (stackV->isEmpty())
                cout << "\nThe stack is empty." << endl;
            else
                cout << "\nThe stack is not empty." << endl;
            break;
        case 'F':
            if (stackV->isFull())
                cout << "\nThe stack is full." << endl;
            else
                cout << "\nThe stack is not full." << endl;
            break;
        case 'P':
            cout << "Value to push: ";
            cin >> value;
            stackV->push(value);
            break;
        case 'O':
            cout << "\nValue popped: " << stackV->pop() << endl;
            break;
        case 'T':
            cout << "\nStack top: " << stackV->topOf() << endl;
            break;
        case 'W':
            cout << "\nTop --> Bottom" << endl;
            stackV->toStream(cout);
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    }
    while (toupper(response) != 'Q');
    return EXIT_SUCCESS;
}

