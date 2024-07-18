#pragma once

#include "Rectangle.h"

class Node
{
public:
    Node(Rectangle rectangle) : rectangle(rectangle), room(rectangle), left(nullptr), right(nullptr) {};
    Rectangle rectangle;
    Rectangle room;
    Node* left;
    Node* right;
    bool has_children();
};