// File: ShapeFactory/Circle.cpp

#include <cassert>

#include "Circle.hpp"
#include "Utilities.hpp"  // PI.

Circle::Circle(double radius) {  
    assert(radius >= 0.0);
    _radius = radius;
}

double Circle::area() {  
    return PI * _radius * _radius;
}

double Circle::perimeter() {  
    return 2.0 * PI * _radius;
}

void Circle::scale(double factor) {  
    // Exercise for the student.
}

void Circle::display() {
    cout << "Circle\n" << "Radius: " << _radius << endl;
}

void Circle::promptAndSetDimensions() {
    _radius = promptDoubleGE("Radius?", 0.0);
}

