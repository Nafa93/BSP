#pragma once

#include "Node.h"
#include "RandomNumberGenerator.h"

#include <vector>

class Tree {
public:
    Tree(Node node) : root(node), rng(RandomNumberGenerator()) { }
    void partition(Node* node, int depth, int max_depth);
    Node root;
    vector<Rectangle> rooms;
    vector<Rectangle> areas;
    vector<Rectangle> corridors;
    vector<Node*> leaves;
    void generate_corridors(Node* node);

private:
    RandomNumberGenerator rng;

    void generate_room(Node* node);
    void generate_vertical_corridor(Node* origin, Node* end);
    void generate_horizontal_corridor(Node* origin, Node* end);
    void generate_corridor(Node* origin, Node* end);
};