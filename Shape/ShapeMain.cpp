// File: Shape/ShapeMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.

#include "Utilities.hpp" // promptIntBetween, promptDoubleGE.
#include "AShape.hpp"
#include "Line.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "RightTriangle.hpp"
#include "NullShape.hpp"
#include "ShapeMain.hpp"
#include "MysteryShape.hpp"

int main() {
    const int NUM_SHAPES = 5;
    shared_ptr<AShape> shapes[NUM_SHAPES];
    initialize(shapes, NUM_SHAPES);
    promptLoop(shapes, NUM_SHAPES);
    return EXIT_SUCCESS;
}

void initialize(shared_ptr<AShape> shapes[], int cap) {
    for (int i = 0; i < cap; i++) {
        shapes[i] = make_shared<NullShape>();
    }
}

void promptLoop(shared_ptr<AShape> shapes[], int cap) {
    char response = '\0';
    do {
        cout << "\nThere are [0.." << cap - 1 << "] shapes." << endl;
        cout << "(m)ake  (c)lear  (a)rea  (p)erimeter  (s)cale  (d)isplay  "
             << "(q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'M':
            makeShape(shapes[promptIntBetween("Which shape?", 0, cap-1)]);
            break;
        case 'C':
            clearShape(shapes[promptIntBetween("Which shape?", 0, cap-1)]);
            break;
        case 'A':
            printArea(shapes[promptIntBetween("Which shape?", 0, cap-1)]);
            break;
        case 'P':
            printPerimeter(shapes[promptIntBetween("Which shape?", 0, cap-1)]);
            break;
        case 'S':
            scaleShape(shapes[promptIntBetween("Which shape?", 0, cap-1)]);
            break;
        case 'D':
            displayShape(shapes[promptIntBetween("Which shape?", 0, cap-1)]);
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
}

void makeShape(shared_ptr<AShape> &sh) {
    switch (shapeType()) {
    case 'L':
        sh = make_shared<Line>() ;
        break;
    case 'R':
        sh = make_shared<Rectangle>() ;
        break;
    case 'C':
        sh = make_shared<Circle>() ;
        break;
    case 'T':
        sh = make_shared<RightTriangle>() ;
        break;
    case 'M':
        sh = make_shared<MysteryShape>();
        break;
    default:
        break;
    }
    sh->promptAndSetDimensions();
}

char shapeType() {
    char ch;
    cout << "(l)ine  (r)ectangle  (c)ircle  right(t)riangle  (m)ystery: ";
    cin >> ch;
    ch = toupper(ch);
    while (ch != 'L' && ch != 'R' && ch != 'C' && ch != 'T' && ch != 'M') {
        cout << "Must be l, r, c, t, or m.  Which type? ";
        cin >> ch;
        ch = toupper(ch);
    }
    return ch;
}

void clearShape(shared_ptr<AShape> &sh) {
    sh = make_shared<NullShape>() ;
}

void printArea(shared_ptr<AShape> sh) {
    cout << "\nArea: " << sh->area() << endl;
}

void printPerimeter(shared_ptr<AShape> sh) {
    cout << "\nPerimeter: " << sh->perimeter() << endl;
}

void scaleShape(shared_ptr<AShape> sh) {
    sh->scale(promptDoubleGE("Scale factor?", 0.0));
}

void displayShape(shared_ptr<AShape> sh) {
    cout << endl;
    sh->display();
}

