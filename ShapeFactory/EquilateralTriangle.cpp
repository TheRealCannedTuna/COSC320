// File: ShapeFactory/EquilateralTriangle.cpp

#include <cassert>
#include <cmath> // sqrt function
#include "Utilities.hpp"
#include "EquilateralTriangle.hpp"

EquilateralTriangle::EquilateralTriangle(double side) {
    assert(side >= 0.0);
    _side = side;
}

double EquilateralTriangle::area() {
    return sqrt(3.0) * _side * _side / 4.0;
}

double EquilateralTriangle::perimeter() {
    return 3.0 * _side;
}

void EquilateralTriangle::scale(double factor) {
    // Exercise for the student.
}

void EquilateralTriangle::display() {
    cout << "Equilateral Triangle\n" << "Side: " << _side << endl;
}

void EquilateralTriangle::promptAndSetDimensions() {
    _side = promptDoubleGE("Side?", 0.0);
}
