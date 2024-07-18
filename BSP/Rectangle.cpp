#include "Rectangle.h"

Coordinate Rectangle::top_right_corner() {
	return Coordinate(origin.x + width - 1, origin.y);
}

Coordinate Rectangle::top_left_corner() {
	return origin;
}

Coordinate Rectangle::bottom_right_corner() {
	return Coordinate(origin.x + width - 1, origin.y + height - 1);
}

Coordinate Rectangle::bottom_left_corner() {
	return Coordinate(origin.x, origin.y + height - 1);
}