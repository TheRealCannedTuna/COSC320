// File: ShapeFactory/ShapeFactory0.hpp

#ifndef ShapeFactory0_hpp
#define ShapeFactory0_hpp

#include "AShapeFactory.hpp"

/**
 * Manufactures NullShape.
 * Null Object pattern.
 */
class ShapeFactory0 : public AShapeFactory{
public:
    shared_ptr<AShape> makeShape(char shapeType = 'N') override;
    // Post: A pointer to a NullShape object is returned.

    char promptShapeType() override;
    // Does nothing.
    // Post: Null character is returned.
};

#endif
