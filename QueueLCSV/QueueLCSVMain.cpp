// File: QueueLCSV/QueueLCSVMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "QueueLCSV.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    shared_ptr<AQueue<double>>
        queueLCSV = make_shared<QueueLCSV<double>>(promptIntGE("Queue capacity", 1));
    double value;
    char cResponse;
    do {
        cout << "\n(e)mpty  (f)ull  e(n)queue  (d)equeue  (h)ead  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'E':
            if (queueLCSV->isEmpty())
                cout << "\nThe queue is empty." << endl;
            else
                cout << "\nThe queue is not empty." << endl;
            break;
        case 'F':
            if (queueLCSV->isFull())
                cout << "\nThe queue is full." << endl;
            else
                cout << "\nThe queue is not full." << endl;
            break;
        case 'N':
            cout << "Value to enqueue: ";
            cin >> value;
            queueLCSV->enqueue(value);
            break;
        case 'D':
            cout << "\nValue dequeued: " << queueLCSV->dequeue() << endl;
            break;
        case 'H':
            cout << "\nQueue head: " << queueLCSV->headOf() << endl;
            break;
        case 'W':
            cout << "\nHead --> Tail" << endl;
            queueLCSV->toStream(cout);
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

