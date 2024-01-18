// File: QueueA/QueueAMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "QueueA.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    shared_ptr<AQueue<double>>
        queueA = make_shared<QueueA<double>>(promptIntGE("Queue capacity", 1));
    double value;
    char cResponse;
    do {
        cout << "\n(e)mpty  (f)ull  e(n)queue  (d)equeue  (h)ead  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'E':
            if (queueA->isEmpty())
                cout << "\nThe queue is empty." << endl;
            else
                cout << "\nThe queue is not empty." << endl;
            break;
        case 'F':
            if (queueA->isFull())
                cout << "\nThe queue is full." << endl;
            else
                cout << "\nThe queue is not full." << endl;
            break;
        case 'N':
            cout << "Value to enqueue: ";
            cin >> value;
            queueA->enqueue(value);
            break;
        case 'D':
            cout << "\nValue dequeued: " << queueA->dequeue() << endl;
            break;
        case 'H':
            cout << "\nQueue head: " << queueA->headOf() << endl;
            break;
        case 'W':
            cout << "\nHead --> Tail" << endl;
            queueA->toStream(cout);
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

