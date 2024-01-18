// File: Shape/MysteryShape.hpp
// Exercise for the student.

#ifndef MysteryShape_hpp
#define MysteryShape_hpp

#include "AShape.hpp"

class MysteryShape : public AShape {
private:
    double _side_length;

public:
    explicit MysteryShape(double side_length = 0.0);
    // Pre: side_length > 0.0.
    // Post: This "mystery shape" is initialized with a side length;

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

