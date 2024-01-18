// File: Dictionary/DictionaryMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream>
#include <string>
using namespace std;

#include "DictionaryBST.hpp"

int main() {
    DictionaryBST<int, string> treeDict;
    int key;
    string value;
    char response;
    do {
        cout << "\n(c)lear  (i)nsert  (r)emove  co(n)tains  (w)rite  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'C':
            treeDict.clear();
            break;
        case 'I':
            cout << "Insert what integer key? ";
            cin >> key;
            cout << "Insert what string value? ";
            cin >> value;
            treeDict.insert(key, value);
            break;
        case 'R':
            cout << "Remove what integer key? ";
            cin >> key;
            if (treeDict.remove(key, value)) {
                cout << "\nKey " << key << " removed with a value of " << value << "." << endl;
            }
            else {
                cout << "\nKey " << key << " is not in the dictionary." << endl;
            }
            break;
        case 'N':
            cout << "Search for what integer key? ";
            cin >> key;
            if (treeDict.contains(key, value)) {
                cout << "\nThe value for key " << key << " is " << value << "." << endl;
            }
            else {
                cout << "\nKey " << key << " is not in the dictionary." << endl;
            }
            break;
        case 'W':
            cout << endl << treeDict << endl;
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
