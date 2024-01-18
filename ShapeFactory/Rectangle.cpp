// File: ShapeFactory/Rectangle.cpp

#include <cassert>

#include "Rectangle.hpp"
#include "Utilities.hpp"

Rectangle::Rectangle(double length, double width) {  
    assert(length >= 0.0 && width >= 0.0);
    _length = length;
    _width  = width;
}

double Rectangle::area() {  
    return _length * _width;
}

double Rectangle::perimeter() {  
    return 2.0 *(_length + _width);
}

void Rectangle::scale(double factor) {  
    // Exercise for the student.
}

void Rectangle::display() {
    cout << "Rectangle" << endl;
    cout << "Length: " << _length << endl;
    cout << "Width: " << _width << endl;
}

void Rectangle::promptAndSetDimensions() {
    _length = promptDoubleGE("Length?", 0.0);
    _width = promptDoubleGE("Width?", 0.0);
}

