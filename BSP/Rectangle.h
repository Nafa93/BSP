#pragma once

#include "Coordinate.h"

class Rectangle
{
public:
    Rectangle(Coordinate origin, int height, int width) : origin(origin), height(height), width(width) {};
    Coordinate origin;
    int height;
    int width;
};
