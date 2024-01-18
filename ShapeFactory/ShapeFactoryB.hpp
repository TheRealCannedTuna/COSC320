// File: ShapeFactory/ShapeFactoryB.hpp

#ifndef ShapeFactoryB_hpp
#define ShapeFactoryB_hpp

#include "AShapeFactory.hpp"

/**
 * Manufactures Ellipse, Equilateral triangle, and Mystery shape.
 */
class ShapeFactoryB : public AShapeFactory{
public:
    shared_ptr<AShape> makeShape(char shapeType = 'N') override;
    // Post: A pointer to a shape of type shapeType is returned.
    // shapeType E for Ellipse, T for Equilateral Triangle, and M for Mystery shape.

    char promptShapeType() override;
    // Prompts user for shape letter, lowercase or uppercase.
    // Post: Uppercase character E, T, or M is returned.
};

#endif
