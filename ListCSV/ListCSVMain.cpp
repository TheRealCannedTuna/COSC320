// File: ListCSV/ListCSVMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.

#include "Utilities.hpp" // promptIntBetween.
#include "ListCSV.hpp"
#include "ArrayT.hpp"
#include "LCSVtoStreamVis.hpp"
#include "LCSVisEmptyVis.hpp"
#include "LCSVclearVis.hpp"
#include "LCSVconcatVis.hpp"
#include "LCSVappendVis.hpp"
#include "LCSVremLastVis.hpp"
#include "LCSVremoveVis.hpp"
#include "LCSVzipVis.hpp"
#include "LCSVunZipVis.hpp"
#include "LCSVreverseVis.hpp"
#include "LCSVlengthVis.hpp"
#include "LCSVmaxVis.hpp"
#include "LCSVcontainsVis.hpp"
#include "LCSVequalsVis.hpp"

const int NUM_LISTS = 5;

typedef ListCSV<int> ListCSVInt;
typedef ArrayT<shared_ptr<ListCSVInt>> ArraySPListInt;

int main() {
    ArraySPListInt lists(NUM_LISTS);
    int value;
    int listNum, listNum2;
    for (int i = 0; i < NUM_LISTS; i++) {
        lists[i] = make_shared<ListCSVInt>();
    }
    char response;
    do {
        cout << "\nThere are [0.." << NUM_LISTS - 1 << "] mutable lists." << endl;
        cout << "(f)irst        s(e)tFirst  (p)repend     removeF(i)rst  cl(o)ne  (c)lear\n"
             << "conca(t)enate  (a)ppend    removeLa(s)t  remove(V)alue  (z)ip    (u)nzip\n"
             << "(r)everse      len(g)th    (m)ax         co(n)tains     equa(l)  (w)rite\n"
             << "(q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'F':
            listNum = promptIntBetween("First element of which list? ", 0, NUM_LISTS - 1);
            if (isEmpty(*lists[listNum])) {
                cout << "\nThe list is empty." << endl;
            } else {
                cout << "\nThe first element is " << lists[listNum]->first() << endl;
            }
            break;
        case 'E':
            cout << "Set first to what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Set first of which list? ", 0, NUM_LISTS - 1);
            if (isEmpty(*lists[listNum])) {
                cout << "\nThe list is empty." << endl;
            } else {
                lists[listNum]->first() = value;
            }
            break;
        case 'P':
            cout << "Prepend what integer value? ";
            cin >> value;
            lists[promptIntBetween("Prepend to which list? ", 0, NUM_LISTS - 1)]->prepend(value);
            break;
        case 'I':
            listNum = promptIntBetween("Remove first from which list? ", 0, NUM_LISTS - 1);
            if (isEmpty(*lists[listNum])) {
                cout << "\nThe list is empty." << endl;
            } else {
                cout << "\n" << lists[listNum]->remFirst() << " was removed." << endl;
            }
            break;
        case 'O':
            listNum = promptIntBetween("Clone which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Copy to which list? ", 0, NUM_LISTS - 1);
            *lists[listNum2] = *lists[listNum];
            break;
        case 'C':
            listNum = promptIntBetween("Clear which list? ", 0, NUM_LISTS - 1);
            clear(*lists[listNum]);
            break;
        case 'T':
            listNum = promptIntBetween("Concatenate which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Suffix list? ", 0, NUM_LISTS - 1);
            if (listNum == listNum2) {
                cout << "\nThe lists must be distinct." << endl;
            } else {
                concat(*lists[listNum], *lists[listNum2]);
            }
            break;
        case 'A':
            cout << "Append what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Append to which list? ", 0, NUM_LISTS - 1);
            append(*lists[listNum], value);
            break;
        case 'S':
            listNum = promptIntBetween("Remove last from which list? ", 0, NUM_LISTS - 1);
            if (isEmpty(*lists[listNum])) {
                cout << "\nThe list is empty." << endl;
            } else {
                cout << "\n " << remLast(*lists[listNum]) << " was removed." << endl;
            }
            break;
        case 'V':
            cout << "Remove what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Remove from which list? ", 0, NUM_LISTS - 1);
            remove(*lists[listNum], value);
            break;
        case 'Z':
            listNum = promptIntBetween("Zip which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Combine with which list? ", 0, NUM_LISTS - 1);
            if (listNum == listNum2) {
                cout << "The lists must be distinct." << endl;
            } else {
                zip(*lists[listNum], *lists[listNum2]);
            }
            break;
        case 'U':
            listNum = promptIntBetween("Unzip which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Split off to which list? ", 0, NUM_LISTS - 1);
            if (listNum == listNum2) {
                cout << "The lists must be distinct." << endl;
            } else {
                lists[listNum2] = unZip(*lists[listNum]);
            }
            break;
        case 'R':
            listNum = promptIntBetween("Reverse which list? ", 0, NUM_LISTS - 1);
            reverse(*lists[listNum]);
            break;
        case 'G':
            listNum = promptIntBetween("Length of which list? ", 0, NUM_LISTS - 1);
            cout << "\nThe length of the list is " << length(*lists[listNum]) << endl;
            break;
        case 'M':
            listNum = promptIntBetween("Maximum of which list? ", 0, NUM_LISTS - 1);
            if (isEmpty(*lists[listNum])) {
                cout << "\nThe list is empty." << endl;
            } else {
                cout << "\nThe maximum element is " << max(*lists[listNum]) << endl;
            }
            break;
        case 'N':
            cout << "Search for what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Search which list? ", 0, NUM_LISTS - 1);
            if (contains(*lists[listNum], value)) {
                cout << "\nThe list contains " << value << "." << endl;
            } else {
                cout << "\nThe list does not contain " << value << "." << endl;
            }
            break;
        case 'L':
            listNum = promptIntBetween("First list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Second list? ", 0, NUM_LISTS - 1);
            if (*lists[listNum] == *lists[listNum2]) {
                cout << "\nThe lists are equal." << endl;
            } else {
                cout << "\nThe lists are not equal." << endl;
            }
            break;
        case 'W':
            listNum = promptIntBetween("Write which list? ", 0, NUM_LISTS - 1);
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
