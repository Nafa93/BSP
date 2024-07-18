#pragma once

#include "Node.h"
#include "RandomNumberGenerator.h"

#include <vector>

class Tree {
public:
    Tree(Node node) : root(node), rng(RandomNumberGenerator()), root_center(Coordinate(node.room.width / 2, node.room.height / 2)) {}
    void partition(Node* node, int depth, int max_depth);
    Node root;
    Coordinate root_center;
    vector<Rectangle> rooms;
    vector<Rectangle> areas;
    vector<Rectangle> corridors;
    vector<Node*> leaves;
    Node* generate_corridors(Node* node);

private:
    RandomNumberGenerator rng;

    void generate_room(Node* node);
    void generate_vertical_corridor(Node* origin, Node* end);
    void vertical_z_shape_corridor(Node* origin, Node* end);
    void generate_horizontal_corridor(Node* origin, Node* end);
    void horizontal_z_shape_corridor(Node* origin, Node* end);
    Node* generate_corridor(Node* origin, Node* end);
};