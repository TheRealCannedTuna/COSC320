// File: Shape/ShapeMain.hpp

#ifndef ShapeMain_hpp
#define ShapeMain_hpp

#include <memory>

#include "AShape.hpp"

void initialize(shared_ptr<AShape> shapes[], int cap);
// Pre: shapes[0..cap - 1] is allocated.
// Post: All shapes[0..cap - 1] are initialized to the null shape.

void promptLoop(shared_ptr<AShape> shapes[], int cap);
// Loop to prompt the user with the top-level main prompt.
// Post: User has selected the quit option.

void makeShape(shared_ptr<AShape> &sh);
// Prompts user for dimensions.
// Post: New sh is created.

char shapeType();
// Prompts user for shape letter, lowercase or uppercase.
// Post: Uppercase character L, R, C, T, or M is returned.

void clearShape(shared_ptr<AShape> &sh);
// Post: sh is made the null shape.

void printArea(shared_ptr<AShape> sh);
// Post: sh's area is printed to standard output.

void printPerimeter(shared_ptr<AShape> sh);
// Post: The perimeter of this sh is printed to standard output.

void scaleShape(shared_ptr<AShape> sh);
// Prompts user for scale factor.
// Post: sh's dimensions are multiplied by the factor.

void displayShape(shared_ptr<AShape> sh);
// Post: sh's name and dimensions are printed to standard output.

#endif
