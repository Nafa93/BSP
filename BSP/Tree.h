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

private:
    RandomNumberGenerator rng;

    void generate_room(Node* node);
};