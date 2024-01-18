// File: ShapeFactory/NullShape.cpp

#include <cassert>
#include "NullShape.hpp"

NullShape::NullShape() {
}

double NullShape::area() {
    return 0.0;
}

double NullShape::perimeter() {
    return 0.0;
}

void NullShape::scale(double factor) {  
    // Exercise for the student.
}

void NullShape::display() {
    cout << "NullShape" << endl;
}

void NullShape::promptAndSetDimensions() {
}

