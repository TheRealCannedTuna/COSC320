// File: SortInt/SortIntMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.

#include "Utilities.hpp"
#include "ArrayT.hpp" // readStream, writeStream.
#include "ASorter.hpp"
#include "MergeSorter.hpp"
#include "QuickSorter.hpp"
#include "InsertSorter.hpp"
#include "SelectSorter.hpp"
#include "HeapSorter.hpp"

using namespace std;

int main() {
    char response;
    ArrayT<int> array(promptIntGE("Enter array capacity", 1));
    shared_ptr<ASorter<int>> sorter;
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = array.fromStream(ifs);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeFormatted(cout, array, length, 16, 6, 6);
        cout << "(m)erge  (q)uick  (i)nsert  (s)elect  (h)eap: ";
        cin >> response;
        switch (toupper(response)) {
        case 'M':
            sorter = make_shared<MergeSorter<int>>(length);
            break;
        case 'Q':
            sorter = make_shared<QuickSorter<int>>();
            break;
        case 'I':
            sorter = make_shared< InsertSorter<int>>();
            break;
        case 'S':
            sorter = make_shared< SelectSorter<int>>();
            break;
        case 'H':
            sorter = make_shared< HeapSorter<int>>(array, 0, length - 1);
            break;
        default:
            break;
        }
        sorter->sort(array, 0, length - 1);
        cout << "Array data:" << endl;
        writeFormatted(cout, array, length, 16, 6, 6);
    }
    return EXIT_SUCCESS;
}

