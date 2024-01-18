// File: DictionaryV/DictionaryVMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream>
#include <string>

#include "ADictionary.hpp"
#include "DictionaryV.hpp"
#include "Utilities.hpp"

using namespace std;

int main() {
    DictionaryV<int, string> vectorDict(promptIntGE("Dictionary capacity", 1));
    int key;
    string value;
    char response;
    do {
        cout << "\n(c)lear  (f)ull  (i)nsert  (r)emove  co(n)tains  (w)rite  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'C':
            vectorDict.clear();
            break;
        case 'F':
            if (vectorDict.isFull())
                cout << "\nThe dictionary is full." << endl;
            else
                cout << "\nThe dictionary is not full." << endl;
            break;
        case 'I':
            cout << "Insert what integer key? ";
            cin >> key;
            cout << "Insert what string value? ";
            cin >> value;
            vectorDict.insert(key, value);
            break;
        case 'R':
            cout << "Remove what integer key? ";
            cin >> key;
            if (vectorDict.remove(key, value)) {
                cout << "\nKey " << key << " removed with a value of " << value << "." << endl;
            }
            else {
                cout << "\nKey " << key << " is not in the dictionary." << endl;
            }
            break;
        case 'N':
            cout << "Search for what integer key? ";
            cin >> key;
            if (vectorDict.contains(key, value)) {
                cout << "\nThe value for key " << key << " is " << value << "." << endl;
            }
            else {
                cout << "\nKey " << key << " is not in the dictionary." << endl;
            }
            break;
        case 'W':
            cout << endl << vectorDict << endl;
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
