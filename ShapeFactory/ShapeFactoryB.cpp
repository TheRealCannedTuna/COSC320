// File: ShapeFactory/ShapeFactoryB.cpp

#include <cctype>  // toupper.

#include "NullShape.hpp"
#include "Ellipse.hpp"
#include "EquilateralTriangle.hpp"
#include "MysteryShape.hpp"  // Exercise for the student.
#include "ShapeFactoryB.hpp"

shared_ptr<AShape> ShapeFactoryB::makeShape(char shapeType) {
    switch (shapeType) {
    case 'E':
        return make_shared<Ellipse>();
    case 'T':
        return make_shared<EquilateralTriangle>();
    case 'M':
        // Exercise for the student.
        break;
    default:
        return make_shared<NullShape>();
    }
}

char ShapeFactoryB::promptShapeType() {
    char ch = '\0';
    cout << "(e)llipse  equilateral(t)riangle  (m)ystery: ";
    cin >> ch;
    ch = toupper(ch);
    while (ch != 'E' && ch != 'T' && ch != 'M') {
        cout << "\nMust be e, t, or m.  Which type? ";
        cin >> ch;
        ch = toupper(ch);
    }
    return ch;
}
