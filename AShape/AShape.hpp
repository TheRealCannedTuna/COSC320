// File: AShape/AShape.hpp

#ifndef AShape_hpp
#define AShape_hpp

#include <iostream> // ostream.
using namespace std;

class AShape {
public:
    virtual ~AShape() = default;
    // Virtual destructor necessary for subclassing.

    virtual double area() = 0;
    // Post: The area of this shape is returned.

    virtual double perimeter() = 0;
    // Post: The perimeter of this shape is returned.

    virtual void scale(double factor) = 0;
    // Pre: factor > 0.0
    // Post: This shape's dimensions are multiplied by factor.

    virtual void display() = 0;
    // Post: This shape's name and dimensions are printed to cout.

    virtual void promptAndSetDimensions() = 0;
    // Post: This shape's dimensions are prompted and set.
    // No dimension is negative.
};

#endif
