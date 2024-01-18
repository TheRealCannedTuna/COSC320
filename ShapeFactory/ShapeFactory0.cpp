// File: ShapeFactory/ShapeFactory0.cpp

#include "NullShape.hpp"
#include "ShapeFactory0.hpp"

shared_ptr<AShape> ShapeFactory0::makeShape(char /*not used*/) {
    return make_shared<NullShape>();
}

char ShapeFactory0::promptShapeType() {
    return '\0';
}
