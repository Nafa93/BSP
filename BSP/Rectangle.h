#pragma once

#include "Coordinate.h"

class Rectangle
{
public:
    Rectangle(Coordinate origin, int height, int width) : origin(origin), height(height), width(width) {};
    Coordinate origin;
    int height;
    int width;
    Coordinate top_right_corner();
    Coordinate top_left_corner();
    Coordinate bottom_right_corner();
    Coordinate bottom_left_corner();
};
