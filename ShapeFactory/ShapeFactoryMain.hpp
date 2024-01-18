// File: ShapeFactory/ShapeFactoryMain.hpp

#ifndef ShapeFactoryMain_hpp
#define ShapeFactoryMain_hpp

#include "AShapeFactory.hpp"

void testShapeFactory(char factoryType = '\0');
// Pre: There exist three shape factories: ShapeFactory0, ShapeFactoryA, ShapeFactoryB.
// Post: if factoryType == 'A', ShapeFactoryA is loaded and tested,
//       else if factoryType == 'B', ShapeFactoryB is loaded and tested,
//       else ShapeFactory0 is loaded and tested.

void initialize(shared_ptr<AShape> shapes[], int cap, shared_ptr<AShapeFactory> shapeFactory);
// Post: All elements shapes are initialized as shared_ptr to the null shape.

void promptLoop(shared_ptr<AShape> shapes[], int cap, shared_ptr<AShapeFactory> shapeFactory);
// Loop to prompt the user with the top-level main prompt.
// Post: User has selected the quit option.

#endif
