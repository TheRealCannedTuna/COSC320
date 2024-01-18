// File: Shape/RightTriangle.cpp

#include <cmath> // sqrt.


#include "RightTriangle.hpp"
#include "Utilities.hpp"

RightTriangle::RightTriangle(double base, double height) {
    if (base < 0.0 || height < 0.0) {
        cerr << "Base and height must not be negative." << endl;
        throw -1;
    }
    _base = base;
    _height = height;
}

double RightTriangle::area() {
    return (_base * _height) / 2;
}

double RightTriangle::perimeter() {
    double hypotenuse = sqrt(_height * _height + _base * _base);
    return _height + _base + hypotenuse;
}

void RightTriangle::scale(double factor) {
    if (factor < 0.0) {
        cerr << "Scaling factor must not be negative." << endl;
        throw -1;
    }
    _base = _base * factor;
    _height = _height * factor;
}

void RightTriangle::display() {
    cout << "Right Triangle" << endl;
    cout << "Base: " << _base << endl;
    cout << "Height: " << _height << endl;
}

void RightTriangle::promptAndSetDimensions() {
    _base = promptDoubleGE("Base?", 0.0);
    _height = promptDoubleGE("Height?", 0.0);
}
