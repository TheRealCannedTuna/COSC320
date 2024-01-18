// File: Shape/Line.cpp

#include "Line.hpp"
#include "Utilities.hpp"

Line::Line(double length) {  
    if(length < 0.0) {
        cerr << "Length must not be negative." << endl;
        throw -1;
    }
    _length = length;
}

double Line::area() {  
    return 0.0;
}

double Line::perimeter() {  
    return _length;
}

void Line::scale(double factor) {  
    if (factor < 0.0 ) {
        cerr << "Scaling factor must not be negative." << endl;
        throw -1;
    }
    _length = _length * factor;
}

void Line::display() {
    cout << "Line\n" << "Length: " << _length << endl;
}

void Line::promptAndSetDimensions() {
    _length = promptDoubleGE("Length?", 0.0);
}

