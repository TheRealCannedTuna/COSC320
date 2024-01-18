// File: SortClassic/SortClassicMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.

#include "Utilities.hpp"
#include "ArrayT.hpp" // readStream, writeStream.

using namespace std;

typedef ArrayT<int> Array;

template<class T>
void sort(ASeq<T> &a, int lo, int hi);

int main() {
    Array array(promptIntGE("Enter array capacity", 1));
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = array.fromStream(ifs);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeFormatted(cout, array, length, 16, 6, 6);
        int low = promptIntBetween("Low index: ", 0, length - 1);
        int high = promptIntBetween("High index: ", 0, length - 1);
        sort(array, low, high);
        cout << "Array data:" << endl;
        writeFormatted(cout, array, length, 16, 6, 6);
    }
    return EXIT_SUCCESS;
}

/**
 * Classic selection sort.
 *
 * @tparam T
 * @param a
 * @param lo
 * @param hi
 */
template<class T>
void sort(ASeq<T> &a, int lo, int hi) {
    cerr << "sort: Exercise for the student." << endl;
    throw -1;
}
