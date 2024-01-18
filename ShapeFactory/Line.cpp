// File: ShapeFactory/Line.cpp

#include <cassert>

#include "Line.hpp"
#include "Utilities.hpp"

Line::Line(double length) {  
    assert(length >= 0.0);
    _length = length;
}

double Line::area() {  
    return 0.0;
}

double Line::perimeter() {  
    return _length;
}

void Line::scale(double factor) {  
    // Exercise for the student.
}

void Line::display() {
    cout << "Line\n" << "Length: " << _length << endl;
}

void Line::promptAndSetDimensions() {
    _length = promptDoubleGE("Length?", 0.0);
}

