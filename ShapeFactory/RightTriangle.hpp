// File: ShapeFactory/RightTriangle.hpp

#ifndef RightTriangle_hpp
#define RightTriangle_hpp

#include "AShape.hpp"

class RightTriangle : public AShape {
private:
    double _base;
    double _height;

public:
    RightTriangle(double base = 0.0, double height = 0.0);
    // Pre: base >= 0.0 and height >= 0.0.
    // Post: This rectangle is initialized with base base and height height.

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

