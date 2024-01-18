// File: ShapeFactory/Rectangle.hpp

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "AShape.hpp"

class Rectangle : public AShape {
private:
    double _length;
    double _width;

public:
    Rectangle(double length = 0.0, double width = 0.0);
    // Pre: length >= 0.0 and width >= 0.0.
    // Post: This rectangle is initialized with
    // length length and width width.

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

