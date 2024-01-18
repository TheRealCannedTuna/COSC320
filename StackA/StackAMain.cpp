// File: StackA/SmartStackAMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "StackA.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    shared_ptr<AStack<double>>
        stackA = make_shared<StackA<double>>(promptIntGE("Stack capacity", 1));
    double value;
    char response;
    do {
        cout << "\n(e)mpty  (f)ull  (p)ush  p(o)p  (t)op  (w)rite  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'E':
            if (stackA->isEmpty())
                cout << "\nThe stack is empty." << endl;
            else
                cout << "\nThe stack is not empty." << endl;
            break;
        case 'F':
            if (stackA->isFull())
                cout << "\nThe stack is full." << endl;
            else
                cout << "\nThe stack is not full." << endl;
            break;
        case 'P':
            cout << "Value to push: ";
            cin >> value;
            stackA->push(value);
            break;
        case 'O':
            cout << "\nValue popped: " << stackA->pop() << endl;
            break;
        case 'T':
            cout << "\nStack top: " << stackA->topOf() << endl;
            break;
        case 'W':
            cout << "\nTop --> Bottom" << endl;
            stackA->toStream(cout);
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

