// File: VectorT/VectorTMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.

#include "15VectorT.hpp"
#include "Utilities.hpp"

using namespace std;

typedef VectorT<int> VectorInt;

int main() {
    VectorInt v;
    int value, index;
    char response;
    do {
        cout << "\n(c)ap  (s)ize  (a)ppend  (i)nsert  (r)emove  se(t)  (w)rite  (q)uit (d)up: ";
        cin >> response;
        switch (toupper(response)) {
        case 'D':
            cout << "\nDuplicated the items in the array." << endl;
            v.dup();
            break;
        case 'C':
            cout << "\nThe capacity is " << v.cap() << endl;
            break;
        case 'S':
            cout << "\nThe size is " << v.size() << endl;
            break;
        case 'A':
            cout << "\nAppend what integer value? ";
            cin >> value;
            v.append(value);
            break;
        case 'I':
            cout << "\nInsert what integer value? ";
            cin >> value;
            cout << "\nInsert at what location? ";
            cin >> index;
            v.insert(index, value);
            break;
        case 'R':
            cout << "\nRemove from what location? ";
            cin >> index;
            value = v.remove(index);
            cout << "\n" << value << " removed" << endl;
            break;
        case 'T':
            cout << "\nSet what integer value? ";
            cin >> value;
            cout << "\nSet at what location? ";
            cin >> index;
            v[index]  = value;
            cout << "\nValue at index " << index << " is now " << v[index] << endl;
            break;
        case 'W':
            cout << "\n" << v << endl;
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
    cout << endl;
    return EXIT_SUCCESS;
}
