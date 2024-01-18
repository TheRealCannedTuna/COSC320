// File: FigureA3/FigureA3Main.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cin, cout.
using namespace std;

int promptAge(); // Function prototype.

int main() { // Main program.
    int age = promptAge();
    if (age < 18) {
        cout << "Tax rate is 0%" << endl;
    } else if (age < 65) {
        cout << "Tax rate is 10%" << endl;
    } else {
        cout << "Tax rate is 5%" << endl;
    }
    return EXIT_SUCCESS;
}

int promptAge() { // Function definition.
    int i = 0;
    cout << "What is your age? ";
    cin >> i;
    while (i <= 0) {
        cout << "Must be greater than 0. Age? ";
        cin >> i;
    }
    return i;
}
