// File: SortProbe/SortProbeMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <iostream> // cout.
#include <fstream>  // ifstream.

#include "Utilities.hpp"
#include "ArrayT.hpp" // readStream, writeStream.
#include "ArrProbe.hpp"
#include "InsertSorter.hpp"
#include "QuickSorter.hpp"
#include "HeapSorter.hpp"
#include "MergeSorter.hpp"
#include "SelectSorter.hpp"

using namespace std;

typedef ArrayT<double> ArrayTD;
typedef ASorter<double> ASorterD;

void testSort(const ArrayTD &arr, int len, shared_ptr<ASorterD> sorter); // Forward declaration.

typedef InsertSorter<double> InsertSorterD;
typedef SelectSorter<double> SelectSorterD;
typedef MergeSorter<double> MergeSorterD;
typedef QuickSorter<double> QuickSorterD;
typedef MergeSorter<double> MergeSorterD;
typedef HeapSorter<double> HeapSorterD;
typedef ArrProbe<double> ArrProbeD;

int main() {
    ArrayTD array(promptIntGE("Enter array capacity", 1));
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = array.fromStream(ifs);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeFormatted(cout, array, length, 16, 6, 6);

        cout << "\nInsertion Sort..." << endl;
        shared_ptr<ASorterD> sorter = make_shared<InsertSorterD>();
        testSort(array, length, sorter);

        cout << "\nSelection Sort..." << endl;
        sorter = make_shared<SelectSorterD>() ;
        testSort(array, length, sorter);

        cout << "\nMerge Sort..." << endl;
        sorter = make_shared<MergeSorterD>(length);
        testSort(array, length, sorter);

        cout << "\nHeapSort Sort..." << endl;
        sorter = make_shared<HeapSorterD>(array, 0, length -1);
        testSort(array, length, sorter);

        cout << "\nQuick Sort..." << endl;
        sorter = make_shared<QuickSorterD>() ;
        testSort(array, length, sorter);
    }
    return EXIT_SUCCESS;
}

void testSort(const ArrayTD &arr, int len, shared_ptr<ASorterD> sorter) {
    ArrayTD tempArr(len);
    for (int i = 0; i < len; i++) {
        tempArr[i] = arr[i];
    }

    ArrProbeD ArrProbe(tempArr);
    ArrProbe.clearProbeCount();
    cout << "\nInitial Performance count:" << endl;
    cout << "Probe count = " << ArrProbe.getProbeCount() << endl;
    sorter->sort(ArrProbe, 0, len - 1);
    bool sorted = true;
    for (int i = 1; i < len; i++) {
        if (tempArr[i-1] > tempArr[i]) {
            sorted = false;
        }
    }
    if (sorted) {
        cout << "\nSorted postcondition satisfied." << endl;
    }
    else {
        cout << "\nERROR: Sorted postcondition not satisfied." << endl;
    }

    cout << "\nSorted Array:" << endl;
    writeFormatted(cout, tempArr, len, 16, 6, 6);
    cout << "\nFinal Performance count:" << endl;
    cout << "Probe count = " << ArrProbe.getProbeCount() << endl;
}
