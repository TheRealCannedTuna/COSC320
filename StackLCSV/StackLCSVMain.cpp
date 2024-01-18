// File: StackLCSV/StackLCSVMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <cctype>   // toupper.

#include "StackLCSV.hpp"
#include "Utilities.hpp"

int main() {
    shared_ptr<AStack<double>>
        _stackLCSV = make_shared<StackLCSV<double>>(promptIntGE("Stack capacity", 1));
    double value;
    char cResponse;
    do {
        cout << "\n(e)mpty  (f)ull  (p)ush  p(o)p  (t)op  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'E':
            if (_stackLCSV->isEmpty())
                cout << "\nThe stack is empty." << endl;
            else
                cout << "\nThe stack is not empty." << endl;
            break;
        case 'F':
            if (_stackLCSV->isFull())
                cout << "\nThe stack is full." << endl;
            else
                cout << "\nThe stack is not full." << endl;
            break;
        case 'P':
            cout << "Value to push: ";
            cin >> value;
            _stackLCSV->push(value);
            break;
        case 'O':
            cout << "\nValue popped: " << _stackLCSV->pop() << endl;
            break;
        case 'T':
            cout << "\nStack top: " << _stackLCSV->topOf() << endl;
            break;
        case 'W':
            cout << "\nTop --> Bottom" << endl;
            _stackLCSV->toStream(cout);
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

