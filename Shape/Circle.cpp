// File: Shape/Circle.cpp

#include "Circle.hpp"
#include "Utilities.hpp" // PI.

Circle::Circle(double radius) {  
    if(radius < 0.0) {
        cerr << "Radius must not be negative." << endl;
        throw -1;
    }
    _radius = radius;
}

double Circle::area() {  
    return PI * _radius * _radius;
}

double Circle::perimeter() {  
    return 2.0 * PI * _radius;
}

void Circle::scale(double factor) {  
    if (factor < 0.0 ) {
        cerr << "Scaling factor must not be negative." << endl;
        throw -1;
    }
    _radius *= _radius * factor;
}

void Circle::display() {
    cout << "Circle\n" << "Radius: " << _radius << endl;
}

void Circle::promptAndSetDimensions() {
    _radius = promptDoubleGE("Radius?", 0.0);
}

