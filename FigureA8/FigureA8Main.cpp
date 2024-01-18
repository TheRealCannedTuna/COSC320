// File: FigureA8/FigureA8Main.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cin, cout.
#include "Utilities.hpp" // promptIntGE.
using namespace std;

int main() {
    int iAge = promptIntGE("What is your age? ", 0);
    if (iAge < 18) {
        cout << "Tax rate is 0%" << endl;
    } else if (iAge < 65) {
        cout << "Tax rate is 10%" << endl;
    } else {
        cout << "Tax rate is 5%" << endl;
    }
    return EXIT_SUCCESS;
}
