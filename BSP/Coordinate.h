#pragma once
class Coordinate
{
public:
    Coordinate(int x, int y) : x(x), y(y) {};
    int x;
    int y;

    int distance(Coordinate to);
};