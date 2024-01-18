// File: QueueV/SmartQueueVMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "QueueV.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    shared_ptr<AQueue<double>>
        smartQueueV = make_shared<QueueV<double>>(promptIntGE("Queue capacity", 1));
    double value;
    char cResponse;
    do {
        cout << "\n(e)mpty  (f)ull  e(n)queue  (d)equeue  (h)ead  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'E':
            if (smartQueueV->isEmpty())
                cout << "\nThe queue is empty." << endl;
            else
                cout << "\nThe queue is not empty." << endl;
            break;
        case 'F':
            if (smartQueueV->isFull())
                cout << "\nThe queue is full." << endl;
            else
                cout << "\nThe queue is not full." << endl;
            break;
        case 'N':
            cout << "Value to enqueue: ";
            cin >> value;
            smartQueueV->enqueue(value);
            break;
        case 'D':
            cout << "\nValue dequeued: " << smartQueueV->dequeue() << endl;
            break;
        case 'H':
            cout << "\nQueue head: " << smartQueueV->headOf() << endl;
            break;
        case 'W':
            cout << "\nHead --> Tail" << endl;
            smartQueueV->toStream(cout);
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

