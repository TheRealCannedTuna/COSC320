// File: LLRBTree/LLRBTreeMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.
#include "LLRBTree.hpp"

int main() {
    LLRBTree<int> llrbTree;
    int value;
    char response;
    do {
        cout << "\n(c)ontains  (i)nsert  (r)emove  (w)rite  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'C':
            cout << "Search for what integer value? ";
            cin >> value;
            if (llrbTree.contains(value)) {
                cout << "\nThe tree contains " << value << "." << endl;
            }
            else {
                cout << "\nThe tree does not contain " << value << "." << endl;
            }
            break;
        case 'I':
            cout << "Value to insert: ";
            cin >> value;
            llrbTree.insert(value);
            break;
        case 'R':
            cout << "Value to remove: ";
            cin >> value;
            llrbTree.remove(value);
            break;
        case 'W':
            cout << endl << llrbTree;
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
