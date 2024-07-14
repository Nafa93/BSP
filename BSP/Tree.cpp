#include "Tree.h"

#include <random>

using namespace std;

void Tree::partition(Node* node, int depth, int max_depth) {
    areas.push_back(node->rectangle);

    if (depth == max_depth) {
        generate_room(node);
        rooms.push_back(node->room);
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

void Tree::generate_room(Node* node) {
    int half_height = node->rectangle.height / 2;
    int percent_height = node->rectangle.height * 20 / 100;
    int random_height = rng.generate(half_height - percent_height, half_height + percent_height);

    int half_width = node->rectangle.width / 2;
    int percent_width = node->rectangle.width * 20 / 100;
    int random_width = rng.generate(half_width - percent_width, half_width + percent_width);


    int random_x = rng.generate(node->rectangle.origin.x + 1, node->rectangle.origin.x + node->rectangle.width - random_width - 1);
    int random_y = rng.generate(node->rectangle.origin.y + 1, node->rectangle.origin.y + node->rectangle.height - random_height - 1);

    node->room = Rectangle(Coordinate(random_x, random_y), random_height, random_width);
}