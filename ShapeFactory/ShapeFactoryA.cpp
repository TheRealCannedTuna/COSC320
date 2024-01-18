// File: ShapeFactory/ShapeFactoryA.cpp

#include <cctype>  // toupper.

#include "Line.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "RightTriangle.hpp"
#include "NullShape.hpp"
#include "MysteryShape.hpp"  // Exercise for the student.
#include "ShapeFactoryA.hpp"

shared_ptr<AShape> ShapeFactoryA::makeShape(char shapeType) {
    switch (shapeType) {  
    case 'L':
        return make_shared<Line>();
    case 'R':
        return make_shared<Rectangle>();
    case 'C':
        return make_shared<Circle>();
    case 'T':
        return make_shared<RightTriangle>();
    case 'M':
        // Exercise for the student.
        break;
    default:
        return make_shared<NullShape>();
    }
}

char ShapeFactoryA::promptShapeType() {
    char ch = '\0';
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
