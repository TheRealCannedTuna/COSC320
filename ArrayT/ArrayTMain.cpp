// File: ArrayT/ArrayTMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.

#include "Utilities.hpp"
#include "ArrayT.hpp"

using namespace std;

typedef ArrayT<double> ArrayDouble;

int main() {
    ArrayDouble arr(promptIntGE("Enter array capacity", 1));
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = arr.fromStream(ifs);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeFormatted(cout, arr, length, 16, 1, 6);
        arr[2 * arr.cap()] = 123.4;
        cout << arr[2 * arr.cap()] << endl;
        return EXIT_SUCCESS;
    }
}
