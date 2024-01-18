// File: ShapeFactory/ShapeFactoryMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <cctype>  // toupper.

#include "Utilities.hpp"  // promptDoubleGE.
#include "ShapeFactory0.hpp"
#include "ShapeFactoryA.hpp"
#include "ShapeFactoryB.hpp"
#include "ShapeFactoryMain.hpp"

/**
 * @param argc: argument count >= 1
 * @param argv: if argc == 1, i.e. there is no command line argument, ShapeFactory0 is used.
 *  Otherwise, if argv[1] == "A" then ShapeFactoryA is used,
 *      else if argv[1] == "B" then ShapeFactoryB is used,
 *      else ShapeFactory0 is used.
 * @return EXIT_SUCCESS
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        cout << "\nBegin testing ShapeFactory" << *argv[1] << endl;
        testShapeFactory(*argv[1]);
        cout << "\nDone testing ShapeFactory" << *argv[1] << endl;
    }
    else {
        cout << "\nBegin testing ShapeFactory0" << endl;
        testShapeFactory();
        cout << "\nDone testing ShapeFactory0" << endl;
    }
    cout << "\nMain: DONE!" << endl;
    return EXIT_SUCCESS;
}

void testShapeFactory(char factoryType) {
    shared_ptr<AShapeFactory> shapeFactory;
    const int NUM_SHAPES = 5;
    shared_ptr<AShape> shapes[NUM_SHAPES];

    switch (factoryType) {
    case 'A':
        shapeFactory = make_shared<ShapeFactoryA>();
        break;
    case 'B':
        shapeFactory = make_shared<ShapeFactoryB>();
        break;
    default:
        shapeFactory = make_shared<ShapeFactory0>();
        break;
    }
    initialize(shapes, NUM_SHAPES, shapeFactory);
    promptLoop(shapes, NUM_SHAPES, shapeFactory);
}

void initialize(shared_ptr<AShape> shapes[], int cap, shared_ptr<AShapeFactory> shapeFactory) {
    for (int i = 0; i < cap; i++) {
        shapes[i] = shapeFactory->makeShape();  // fill array with NullShape objects.
    }
}

void promptLoop(shared_ptr<AShape> shapes[], int cap, shared_ptr<AShapeFactory> shapeFactory) {
    char cResponse = '\0';
    int ix = 0;
    do {  
        cout << "\nThere are [0.." << cap - 1 << "] shapes\n" << endl;
        cout << "(m)ake  (c)lear  (a)rea  (p)erimeter  ";
        cout << "(s)cale  (d)isplay  (q)uit: ";
        cin >> cResponse;
        cResponse = toupper(cResponse);
        if (cResponse != 'Q') {
            ix = promptIntBetween("\nWhich shape?", 0, cap - 1);
        }
        switch (cResponse) {
        case 'M':
            cout << "Making a shape for shapes[" << ix << "]:" << endl;
            cout << endl;
            shapes[ix] = shapeFactory->makeShape(shapeFactory->promptShapeType());
            cout << endl;
            shapes[ix]->promptAndSetDimensions();
            break;
        case 'C':
            shapes[ix] = shapeFactory->makeShape();
            break;
        case 'A':
            cout << "\nFor shapes[" << ix << "] ";
            cout << "Area: " << shapes[ix]->area() << endl;
            cout << endl;
            break;
        case 'P':
            cout << "\nFor shapes[" << ix << "] ";
            cout << "Perimeter: " << shapes[ix]->perimeter() << endl;
            cout << endl;
            break;
        case 'S':
            cout << endl;
            shapes[ix]->scale(promptDoubleGE("Scale factor?", 0.0));
            break;
        case 'D':
            cout << "\nFor shapes[" << ix << "] ";
            cout << endl;
            shapes[ix]->display();
            cout << endl;
            break;
        case 'Q':
            break;
        default:
            cout << "\nPlease enter only one of the following characters: ";
            cout << "m, c, a, p, s, n, d, q." << endl;
            break;
        }
    } while (toupper(cResponse) != 'Q');
}

