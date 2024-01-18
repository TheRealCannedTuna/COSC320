// File: ListC/ListCMain.cpp

#include <iostream>
#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.
using namespace std;

#include "Utilities.hpp" // promptIntBetween.
#include "ListC.hpp"
#include "ArrayT.hpp"

const int NUM_LISTS = 5;
bool getValidSourceDest(int &s, int &d); // Forward declaration.

typedef AListC<int> AListCInt;
typedef ArrayT<shared_ptr<AListCInt>> ArrayOfListInt; // An array of  shared pointers to AListCInt.
typedef MTListC<int> MTListInt;
typedef NEListC<int> NEListInt;

int main() {
    ArrayOfListInt lists(NUM_LISTS);
    int value;
    int listNum, source, dest;
    for (int i = 0; i < NUM_LISTS; i++) {
        lists[i] = make_shared<MTListInt>();
    }
    char response;
    do {
        cout << "\nThere are [0.." << NUM_LISTS - 1 << "] immutable lists." << endl;
        cout << "cl(o)ne        (p)repend     (a)ppend       conca(t)enate  (r)everse  len(g)th\n"
             << "(e)mpty        co(n)tains    equa(l)        (m)ax          (f)irst    t(h)eRest\n"
             << "removeF(i)rst  removeLa(s)t  removeVal(u)e  (z)ip          e(v)en     od(d)\n"
             << "(w)rite        (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'O':
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->clone();
            }
            break;
        case 'P':
            cout << "Integer to prepend: ";
            cin >> value;
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->prepend(value);
            }
            break;
        case 'A':
            cout << "Integer to append: ";
            cin >> value;
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->append(value);
            }
            break;
        case 'T':
            listNum = promptIntBetween("Suffix list? ", 0, NUM_LISTS - 1);
            if (getValidSourceDest(source, dest)) {
                if (listNum != source && listNum != dest) {
                    lists[dest] = lists[source]->concat(lists[listNum]);
                } else {
                    cout << "\nThe lists must be distinct." << endl;
                }
            }
            break;
        case 'R':
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->reverse();
            }
            break;
        case 'G':
            listNum = promptIntBetween("Length of which list? ", 0, NUM_LISTS - 1);
            cout << "\nThe length of the list is " << lists[listNum]->length() << endl;
            break;
        case 'E':
            listNum = promptIntBetween("Test which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            } else {
                cout << "\nThe list is not empty." << endl;
            }
            break;
        case 'N':
            cout << "Search for what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Search which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->contains(value)) {
                cout << "\nThe list contains " << value << "." << endl;
            } else {
                cout << "\nThe list does not contain " << value << "." << endl;
            }
            break;
        case 'L':
            source = promptIntBetween("Source list? ", 0, NUM_LISTS - 1);
            dest = promptIntBetween("Destination list? ", 0, NUM_LISTS - 1);
            if (*lists[source] == *lists[dest]) {
                cout << "\nThe lists are equal." << endl;
            } else {
                cout << "\nThe lists are not equal." << endl;
            }
            break;
        case 'M':
            listNum = promptIntBetween("List to get max from? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            } else {
                cout << "\nThe maximum element is " << lists[listNum]->max() << endl;
            }
            break;
        case 'F':
            listNum = promptIntBetween("List to get first from? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            } else {
                auto neListNum = static_pointer_cast<NEListInt>(lists[listNum]);
                cout << "\nThe first element is " << neListNum->first() << endl;
            }
            break;
        case 'H':
            listNum = promptIntBetween("List to get rest from? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            } else {
                auto neListNum = static_pointer_cast<NEListInt>(lists[listNum]);
                cout << "\nThe rest of the list is " << *(neListNum->rest()) << endl;
            }
            break;
        case 'I':
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->remFirst();
            }
            break;
        case 'S':
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->remLast();
            }
            break;
        case 'U':
            cout << "Remove what integer value? ";
            cin >> value;
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->remove(value);
            }
            break;
        case 'Z':
            listNum = promptIntBetween("Shuffle list? ", 0, NUM_LISTS - 1);
            if (getValidSourceDest(source, dest)) {
                if (listNum != source && listNum != dest) {
                    lists[dest] = lists[source]->zip(lists[listNum]);
                } else {
                    cout << "\nThe lists must be distinct." << endl;
                }
            }
            break;
        case 'V':
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->evenIndex();
            }
            break;
        case 'D':
            if (getValidSourceDest(source, dest)) {
                lists[dest] = lists[source]->oddIndex();
            }
            break;
        case 'W':
            listNum = promptIntBetween("List to write? ", 0, NUM_LISTS - 1);
            cout << "\n" << *lists[listNum] << endl;
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
    return EXIT_SUCCESS;
}

bool getValidSourceDest(int &s, int &d) {
    s = promptIntBetween("Source list? ", 0, NUM_LISTS - 1);
    d = promptIntBetween("Destination list? ", 0, NUM_LISTS - 1);
    if (s == d) {
        cout << "The lists must be distinct." << endl;
        return false;
    }
    return true;
}
