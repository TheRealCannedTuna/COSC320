// File: Shape/Circle.hpp

#ifndef Circle_hpp
#define Circle_hpp

#include "AShape.hpp"

class Circle : public AShape {
private:
    double _radius;
public:
    explicit Circle(double radius = 0.0);
    // Pre: radius >= 0.0.
    // Post: This circle is initialized with radius radius.

    double area() override;
    double perimeter() override;
    void scale(double factor) override;
    void display() override;
    void promptAndSetDimensions() override;
};

#endif

