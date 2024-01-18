// File: ShapeFactory/AShapeFactory.hpp

#ifndef AShapeFactory_hpp
#define AShapeFactory_hpp

#include <memory>

#include "AShape.hpp"

/**
 * Example of abstract factory pattern.
 */
class AShapeFactory {
public:

    virtual ~AShapeFactory() = default;
    // Virtual destructor necessary for subclassing.

    virtual shared_ptr<AShape> makeShape(char shapeType = 'N') = 0;
    // Post: A shared_ptr to a shape of type shapeType is returned.

    virtual char promptShapeType() = 0;
    // Prompts user for shape letter, lowercase or uppercase.
    // Post: Uppercase character representing a shape type is returned.
};

#endif

