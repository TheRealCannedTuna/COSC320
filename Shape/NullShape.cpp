// File: Shape/NullShape.cpp

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
    if (factor < 0.0) {
        cerr
                << "Scaling factor must not be negative. But if you've gotten this error message, you've done something very, *very* wrong."
                << endl;
        throw -1;
    }
}

void NullShape::display() {
    cout << "NullShape" << endl;
}

void NullShape::promptAndSetDimensions() {
}

