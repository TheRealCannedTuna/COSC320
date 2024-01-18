//
// Created by Dung Nguyen on 8/3/21.
//
#include <iostream>
#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.
using namespace std;

//#include "Utilities.hpp" // promptIntBetween.
//#include "ArrayT.hpp"
#include "ListCVZ.hpp"
#include "LCVZprependVis.hpp"
#include "LCVZtoStreamVis.hpp"

typedef AListCVZ<int> AListCVZInt;
typedef MTListCVZ<int> MTListCVZInt;
typedef NEListCVZ<int> NEListCVZInt;

int main() {
    shared_ptr<AListCVZInt> myList = make_shared<MTListCVZInt>();
    LCVZtoStreamVis<int> toStreamVis(cout);
    int value;

    {
        value = 10;
        cout << "\n Before declaring prependVis(" << value << ")" << endl;
        myList->accept(toStreamVis);
        LCVZprependVis<int> prependVis(value);
        cout << "\n After declaring prependVis( " << value << ")" << endl;
        myList->accept(toStreamVis);

        cout << "\n Prepend " << value << endl;
        myList = static_pointer_cast<AListCVZInt>(myList->accept(prependVis));
        myList->accept(toStreamVis);
    }
    {
        value = 20;
        cout << "\n Before declaring prependVis(" << value << ")" << endl;
        myList->accept(toStreamVis);
        LCVZprependVis<int> prependVis(value);
        cout << "\n After declaring prependVis( " << value << ")" << endl;
        myList->accept(toStreamVis);

        cout << "\n Prepend " << value << endl;
        myList = static_pointer_cast<AListCVZInt>(myList->accept(prependVis));
        myList->accept(toStreamVis);
    }
    {
//        value = 30;
        cout << "\n Before declaring prependVis(" << 30 << ")" << endl;
        myList->accept(toStreamVis);
        LCVZprependVis<int> prependVis(30);
        cout << "\n After declaring prependVis( " << 30 << ")" << endl;
        myList->accept(toStreamVis);

        cout << "\n Prepend " << 30 << endl;
        myList = static_pointer_cast<AListCVZInt>(myList->accept(prependVis));
        myList->accept(toStreamVis);
    }

    cout << "\nDone."<< endl;

    return EXIT_SUCCESS;
}
