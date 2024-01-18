// File: ShapeFactory/EquilateralTriangle.hpp

#ifndef EquilateralTriangle_hpp
#define EquilateralTriangle_hpp

#include "AShape.hpp"

class EquilateralTriangle : public AShape {
private:
    double _side;
public:
    EquilateralTriangle(double side = 0.0);
    // Pre: side >= 0.0.
    // Post: This EquilateralTriangle is initialized with side side.

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

