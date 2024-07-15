#include "Tree.h"

#include <random>
#include <iostream>

using namespace std;

void Tree::partition(Node* node, int depth, int max_depth) {
    areas.push_back(node->rectangle);

    if (depth == max_depth) {
        generate_room(node);
        rooms.push_back(node->room);
        leaves.push_back(node);
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

void Tree::generate_corridor(Node* origin, Node* end)
{
    bool is_vertical_split = origin->rectangle.origin.x == end->rectangle.origin.x;

    if (is_vertical_split) {
        generate_vertical_corridor(origin, end);
    }
    else {
        cout << "This is a horizontal split" << endl;
    }
}

void Tree::generate_vertical_corridor(Node* origin, Node* end)
{
    Node* top_node;
    Node* bottom_node;

    if (origin->rectangle.origin.y < end->rectangle.origin.y) {
        top_node = origin;
        bottom_node = end;
    }
    else {
        top_node = end;
        bottom_node = origin;
    }

    // Ensures corridor won't be at the wall
    int offset = 2;

    int top_node_wall_x_start = top_node->room.origin.x + offset;
    int top_node_wall_x_end = top_node->room.origin.x + top_node->room.width - offset;
    int top_node_wall_y = top_node->room.origin.y + top_node->room.height - 1;

    int bottom_node_wall_x_start = bottom_node->room.origin.x + offset;
    int bottom_node_wall_x_end = bottom_node->room.origin.x + bottom_node->room.width - offset;
    int bottom_node_wall_y = bottom_node->room.origin.y + 1;

    int corridor_height = (bottom_node_wall_y - top_node_wall_y);

    if (top_node_wall_x_start < bottom_node_wall_x_start && top_node_wall_x_end > bottom_node_wall_x_end) {
        int corridor_start = rng.generate(bottom_node_wall_x_start, bottom_node_wall_x_end);

        corridors.push_back(Rectangle(Coordinate(corridor_start, top_node_wall_y), corridor_height, 1));
    }
    else if (bottom_node_wall_x_start < top_node_wall_x_start && bottom_node_wall_x_end > top_node_wall_x_end) {
        int corridor_start = rng.generate(top_node_wall_x_start, top_node_wall_x_end);

        corridors.push_back(Rectangle(Coordinate(corridor_start, top_node_wall_y), corridor_height, 1));
    }
    else if (top_node_wall_x_start > bottom_node_wall_x_end || top_node_wall_x_end < bottom_node_wall_x_start) {
        int random_start = rng.generate(top_node_wall_x_start, top_node_wall_x_end);
        int random_end = rng.generate(bottom_node_wall_x_start, bottom_node_wall_x_end);

        // Maybe create a z shape
        int first_section_height = corridor_height / 2;
        int second_section_height = corridor_height - first_section_height;
        corridors.push_back(Rectangle(Coordinate(random_start, top_node_wall_y), first_section_height, 1));
        corridors.push_back(Rectangle(Coordinate(random_end, bottom_node_wall_y - second_section_height), second_section_height, 1));

        int z_shape_start = min(random_start, random_end);
        corridors.push_back(Rectangle(Coordinate(z_shape_start, bottom_node_wall_y - second_section_height), 1, abs(random_start - random_end) + 1));
    }
    else if (top_node_wall_x_start < bottom_node_wall_x_start) {
        int corridor_start = rng.generate(bottom_node_wall_x_start, top_node_wall_x_end);

        corridors.push_back(Rectangle(Coordinate(corridor_start, top_node_wall_y), corridor_height, 1));
    }
    else if (top_node_wall_x_start > bottom_node_wall_x_start) {
        int corridor_start = rng.generate(top_node_wall_x_start, bottom_node_wall_x_end);

        corridors.push_back(Rectangle(Coordinate(corridor_start, top_node_wall_y), corridor_height, 1));
    }
}
