// File: ShapeFactory/NullShape.hpp

#ifndef NullShape_hpp
#define NullShape_hpp

#include "AShape.hpp"

class NullShape : public AShape {
public:
    NullShape();
    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

