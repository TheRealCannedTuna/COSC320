// File: CompAssign/CompAssignMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.

#include "Utilities.hpp"
#include "ArrayT.hpp" // readStream, writeStream.
#include "InsertSorter.hpp"
#include "SelectSorter.hpp"
#include "MergeSorter.hpp"
#include "HeapSorter.hpp"
#include "QuickSorter.hpp"
#include "CAMetrics.hpp"

using namespace std;

typedef CAMetrics<double> CAMetricsD;
typedef ArrayT<CAMetricsD> ArrayCAMD;
typedef ASorter<CAMetricsD> ASortCAMD;

void testSort(ArrayCAMD const &arr, int len, shared_ptr<ASortCAMD> sorter); // Forward declaration.

typedef InsertSorter<CAMetricsD> InsertSorterCAMD;
typedef SelectSorter<CAMetricsD> SelectSorterCAMD;
typedef MergeSorter<CAMetricsD> MergeSorterCAMD;
typedef QuickSorter<CAMetricsD> QuickSorterCAMD;
typedef HeapSorter<CAMetricsD> HeapSorterCAMD;

int main() {
    ArrayCAMD array(promptIntGE("Enter array capacity", 1));
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = array.fromStream(ifs);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeFormatted(cout, array, length, 16, 6, 6);

        cout << "\nInsertion Sort..." << endl;
        shared_ptr<ASortCAMD> sorter = make_shared<InsertSorterCAMD>();
        testSort(array, length, sorter);

        cout << "\nSelection Sort..." << endl;
        sorter = make_shared<SelectSorterCAMD>();
        testSort(array, length, sorter);

        cout << "\nMerge Sort..." << endl;
        sorter = make_shared<MergeSorterCAMD>(length);
        testSort(array, length, sorter);

        cout << "\nHeapSort Sort..." << endl;
        sorter = make_shared<HeapSorterCAMD>(array, 0, length - 1);
        testSort(array, length, sorter);

        cout << "\nQuick Sort..." << endl;
        sorter = make_shared<QuickSorterCAMD>();
        testSort(array, length, sorter);
    }
    return EXIT_SUCCESS;
}

void testSort(ArrayCAMD const &arr, int len, shared_ptr<ASortCAMD> sorter) {
    ArrayCAMD tempArr(len);
    for (int i = 0; i < len; i++) {
        tempArr[i] = arr[i];
    }
    CAMetricsD::clearCompareCount();
    CAMetricsD::clearAssignCount();
//    cout << "\nInitial Performance count:" << endl;
//    cout << "Assignment count = " << CAMetricsD::getAssignCount() << endl;
//    cout << "Comparison count = " << CAMetricsD::getCompareCount() << endl;
    sorter->sort(tempArr, 0, len - 1);
    bool sorted = true;
    for (int i = 1; i < len; i++) {
        if (tempArr[i - 1] > tempArr[i]) {
            sorted = false;
        }
    }
    if (sorted) {
//        cout << "\nSorted postcondition satisfied." << endl;
    } else {
        cout << "\nERROR: Sorted postcondition not satisfied." << endl;
    }
    // cout << "\nSorted Arrray:" << endl;
    // writeStream(cout, tempData, iLen);
    cout << "\nFinal Performance count:" << endl;
    cout << "Assignment count = " << CAMetricsD::getAssignCount() << endl;
    cout << "Comparison count = " << CAMetricsD::getCompareCount() << endl;
}

