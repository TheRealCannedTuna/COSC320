// File: StackL/StackLMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <cctype>   // toupper.

#include "StackL.hpp"
#include "Utilities.hpp"

int main() {
    shared_ptr<AStack<double>>
        _stackL = make_shared<StackL<double>>(promptIntGE("Stack capacity", 1));
    double value;
    char cResponse;
    do {
        cout << "\n(e)mpty  (f)ull  (p)ush  p(o)p  (t)op  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'E':
            if (_stackL->isEmpty())
                cout << "\nThe stack is empty." << endl;
            else
                cout << "\nThe stack is not empty." << endl;
            break;
        case 'F':
            if (_stackL->isFull())
                cout << "\nThe stack is full." << endl;
            else
                cout << "\nThe stack is not full." << endl;
            break;
        case 'P':
            cout << "Value to push: ";
            cin >> value;
            _stackL->push(value);
            break;
        case 'O':
            cout << "\nValue popped: " << _stackL->pop() << endl;
            break;
        case 'T':
            cout << "\nStack top: " << _stackL->topOf() << endl;
            break;
        case 'W':
            cout << "\nTop --> Bottom" << endl;
            _stackL->toStream(cout);
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    }
    while (toupper(cResponse) != 'Q');
    return EXIT_SUCCESS;
}

