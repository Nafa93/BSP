#include "Tree.h"

#include <random>

using namespace std;

void Tree::partition(Node* node, int depth, int max_depth) {
    if (depth == max_depth) {
        return;
    }

    bool vertical = depth % 2 == 0;

    if (vertical) {
        int half_height = node->rectangle.height / 2;
        int percent_height = node->rectangle.height * 20 / 100;
        int random_height = rng.generate(half_height - percent_height, half_height + percent_height);

        Rectangle left_rectangle(node->rectangle.origin, random_height, node->rectangle.width);
        Rectangle right_rectangle(Coordinate(node->rectangle.origin.x, node->rectangle.origin.y + random_height), node->rectangle.height - random_height, node->rectangle.width);

        node->left = new Node(left_rectangle);
        node->right = new Node(right_rectangle);

        partition(node->left, depth + 1, max_depth);
        partition(node->right, depth + 1, max_depth);
    }
    else {
        int half_width = node->rectangle.width / 2;
        int percent_width = node->rectangle.width * 20 / 100;
        int random_width = rng.generate(half_width - percent_width, half_width + percent_width);

        Rectangle left_rectangle(node->rectangle.origin, node->rectangle.height, random_width);
        Rectangle right_rectangle(Coordinate(node->rectangle.origin.x + random_width, node->rectangle.origin.y), node->rectangle.height, node->rectangle.width - random_width);

        node->left = new Node(left_rectangle);
        node->right = new Node(right_rectangle);

        partition(node->left, depth + 1, max_depth);
        partition(node->right, depth + 1, max_depth);
    }
}