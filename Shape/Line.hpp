// File: Shape/Line.hpp

#ifndef Line_hpp
#define Line_hpp

#include "AShape.hpp"

class Line : public AShape {
private:
    double _length;

public:
    explicit Line(double length = 0.0);
    // Pre: length >= 0.0.
    // Post: This line is initialized with length length.

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

