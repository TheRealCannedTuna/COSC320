// File: ShapeFactory/Ellipse.hpp

#ifndef Ellipse_hpp
#define Ellipse_hpp

#include "AShape.hpp"

class Ellipse : public AShape {
private:
    double _major;
    double _minor;

public:
    Ellipse(double major = 0.0, double minor = 0.0);
    // Pre: major >= 0.0 and minor >= 0.0.
    // Post: This Ellipse is initialized with major axis major and minor axis minor.

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

