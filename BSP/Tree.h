#pragma once

#include "Node.h"
#include "RandomNumberGenerator.h"

class Tree {
public:
    Tree(Node node) : root(node), rng(RandomNumberGenerator()) { }
    void partition(Node* node, int depth, int max_depth);
    Node root;

private:
    RandomNumberGenerator rng;

    void generate_room(Node* node);
};