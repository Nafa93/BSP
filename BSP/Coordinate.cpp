#include "Coordinate.h"

#include <cmath>

int Coordinate::distance(Coordinate to)
{
    int dx = x - to.x;
    int dy = y - to.y;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}
