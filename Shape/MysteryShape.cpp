// File: Shape/MysteryShape.cpp
// Exercise for the student.

#include <cmath> // sqrt

#include "MysteryShape.hpp"
#include "Utilities.hpp"

double THREEROOTTHREE = 3 * sqrt(3);

MysteryShape::MysteryShape(double side_length) {
    if (side_length < 0.0) {
        cerr << "Side length must not be negative number." << endl;
        throw -1;
    }
    _side_length = side_length;
}

double MysteryShape::area() {
    return (THREEROOTTHREE * _side_length * _side_length) / 2;
}

double MysteryShape::perimeter() {
    return 6 * _side_length;
}

void MysteryShape::scale(double factor) {
    if (factor < 0.0) {
        cerr << "Scaling factor must not be negative." << endl;
        throw -1;
    }
    _side_length = _side_length * factor;
}

void MysteryShape::display() {
    cout << "Regular Hexagon" << endl;
    cout << "Side length: " << _side_length << endl;
}

void MysteryShape::promptAndSetDimensions() {
    _side_length = promptDoubleGE("Side length?", 0.0);
}

