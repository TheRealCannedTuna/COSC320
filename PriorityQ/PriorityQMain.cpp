// File: PriorityQ/PriorityQMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "PriorityQ.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    PriorityQ<int> priorityQ(promptIntGE("Priority queue capacity", 1));
    double value;
    int i;
    char cResponse;
    do {
        cout << "\n(s)ize  (e)mpty  (f)ull  (i)nsert  e(x)tractMax  (m)aximum  increase(K)ey  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'S':
            cout << "\nSize: " << priorityQ.heapSize() << endl;
            break;
        case 'E':
            if (priorityQ.isEmpty())
                cout << "\nThe priority queue is empty." << endl;
            else
                cout << "\nThe priority queue is not empty." << endl;
            break;
        case 'F':
            if (priorityQ.isFull())
                cout << "\nThe priority queue is full." << endl;
            else
                cout << "\nThe priority queue is not full." << endl;
            break;
        case 'I':
            cout << "Insert what integer value? ";
            cin >> value;
            priorityQ.insert(value);
            break;
        case 'X':
            cout << "\nValue extracted: " << priorityQ.extractMax() << endl;
            break;
        case 'M':
            cout << "\nMaximum: " << priorityQ.maximum() << endl;
            break;
        case 'W':
            cout << "\n" << priorityQ << endl;
            break;
        case 'K':
            cout << "Increase key at which index? ";
            cin >> i;
            cout << "Increase to what value? ";
            cin >> value;
            priorityQ.increaseKey(i, value);
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

