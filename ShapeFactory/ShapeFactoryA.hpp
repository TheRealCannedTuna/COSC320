// File: ShapeFactory/ShapeFactoryA.hpp

#ifndef ShapeFactoryA_hpp
#define ShapeFactoryA_hpp

#include "AShapeFactory.hpp"

/**
 * Manufactures Line, Rectangle, Circle, Right triangle, and Mystery shape.
 */
class ShapeFactoryA : public AShapeFactory{
public:
    shared_ptr<AShape> makeShape(char shapeType = 'N') override;
    // Post: A shared_ptr to a shape of type shapeType is returned.
    // shapeType L for Line, R for Rectangle, C for Circle, T for right Triangle, M for Mystery.

    char promptShapeType() override;
    // Prompts user for shape letter, lowercase or uppercase.
    // Post: Uppercase character L, R, C, T, or M is returned.
};

#endif
