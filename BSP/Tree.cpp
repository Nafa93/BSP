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
    int percent_height = node->rectangle.height * 10 / 100;
    int random_height = rng.generate(half_height - percent_height, half_height + percent_height);

    int half_width = node->rectangle.width / 2;
    int percent_width = node->rectangle.width * 10 / 100;
    int random_width = rng.generate(half_width - percent_width, half_width + percent_width);


    int random_x = rng.generate(node->rectangle.origin.x + 1, node->rectangle.origin.x + node->rectangle.width - random_width - 1);
    int random_y = rng.generate(node->rectangle.origin.y + 1, node->rectangle.origin.y + node->rectangle.height - random_height - 1);

    node->room = Rectangle(Coordinate(random_x, random_y), random_height, random_width);
}

Node* Tree::generate_corridor(Node* origin, Node* end)
{
    bool is_vertical_split = origin->rectangle.origin.x == end->rectangle.origin.x;
    bool is_horizontal_split = origin->rectangle.origin.y == end->rectangle.origin.y;

    if (is_vertical_split) {
        generate_vertical_corridor(origin, end);
    }
    else if (is_horizontal_split) {
        generate_horizontal_corridor(origin, end);
    }
    else if (abs(origin->rectangle.origin.x - end->rectangle.origin.x) < abs(origin->rectangle.origin.y - end->rectangle.origin.y)) {
        generate_vertical_corridor(origin, end);
    }
    else {
        generate_horizontal_corridor(origin, end);
    }

    if (root_center.distance(origin->room.origin) < root_center.distance(end->room.origin)) {
        return origin;
    }
    else {
        return end;
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
    int wall_width = 1;

    int top_node_wall_x_start = top_node->room.bottom_left_corner().x + wall_width;
    int top_node_wall_x_end = top_node->room.bottom_right_corner().x - wall_width;
    int top_node_wall_y = top_node->room.bottom_left_corner().y;

    int bottom_node_wall_x_start = bottom_node->room.top_left_corner().x + wall_width;
    int bottom_node_wall_x_end = bottom_node->room.top_right_corner().x - wall_width;
    int bottom_node_wall_y = bottom_node->room.top_right_corner().y + wall_width;

    int corridor_height = (bottom_node_wall_y - top_node_wall_y);

    if (top_node_wall_x_start <= bottom_node_wall_x_start && top_node_wall_x_end >= bottom_node_wall_x_end) {
        int corridor_start = rng.generate(bottom_node_wall_x_start, bottom_node_wall_x_end);

        corridors.push_back(Rectangle(Coordinate(corridor_start, top_node_wall_y), corridor_height, 1));
    }
    else if (bottom_node_wall_x_start <= top_node_wall_x_start && bottom_node_wall_x_end >= top_node_wall_x_end) {
        int corridor_start = rng.generate(top_node_wall_x_start, top_node_wall_x_end);

        corridors.push_back(Rectangle(Coordinate(corridor_start, top_node_wall_y), corridor_height, 1));
    }
    else if (top_node_wall_x_start > bottom_node_wall_x_end || top_node_wall_x_end < bottom_node_wall_x_start) {
        vertical_z_shape_corridor(top_node, bottom_node);
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

void Tree::vertical_z_shape_corridor(Node* origin, Node* end)
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
    int wall_width = 1;

    int top_node_wall_x_start = top_node->room.bottom_left_corner().x + wall_width;
    int top_node_wall_x_end = top_node->room.bottom_right_corner().x - wall_width;
    int top_node_wall_y = top_node->room.bottom_left_corner().y;

    int bottom_node_wall_x_start = bottom_node->room.top_left_corner().x + wall_width;
    int bottom_node_wall_x_end = bottom_node->room.top_right_corner().x - wall_width;
    int bottom_node_wall_y = bottom_node->room.top_right_corner().y + wall_width;

    int corridor_height = (bottom_node_wall_y - top_node_wall_y);

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

void Tree::generate_horizontal_corridor(Node* origin, Node* end) {
    Node* left_node;
    Node* right_node;

    if (origin->rectangle.origin.x < end->rectangle.origin.x) {
        left_node = origin;
        right_node = end;
    }
    else {
        right_node = end;
        left_node = origin;
    }

    // Ensures corridor won't be at the wall
    int wall_width = 1;

    int left_wall_start = left_node->room.top_right_corner().y + wall_width;
    int left_wall_end = left_node->room.bottom_right_corner().y - wall_width;
    int left_wall_x = left_node->room.bottom_right_corner().x;

    int right_wall_start = right_node->room.top_left_corner().y + wall_width;
    int right_wall_end = right_node->room.bottom_left_corner().y - wall_width;
    int right_wall_x = right_node->room.bottom_left_corner().x + wall_width;

    int corridor_width = (right_wall_x - left_wall_x);

    if (left_wall_start <= right_wall_start && left_wall_end >= right_wall_end) {
        int corridor_start = rng.generate(right_wall_start, right_wall_end);

        corridors.push_back(Rectangle(Coordinate(left_wall_x, corridor_start), 1, corridor_width));
    }
    else if (right_wall_start <= left_wall_start && right_wall_end >= left_wall_end) {
        int corridor_start = rng.generate(left_wall_start, left_wall_end);

        corridors.push_back(Rectangle(Coordinate(left_wall_x, corridor_start), 1, corridor_width));
    }
    else if (left_wall_start > right_wall_end || left_wall_end < right_wall_start) {
        horizontal_z_shape_corridor(left_node, right_node);
    }
    else if (left_wall_start < right_wall_start) {
        int corridor_start = rng.generate(right_wall_start, left_wall_end);

        corridors.push_back(Rectangle(Coordinate(left_wall_x, corridor_start), 1, corridor_width));
    }
    else if (left_wall_start > right_wall_start) {
        int corridor_start = rng.generate(left_wall_start, right_wall_end);

        corridors.push_back(Rectangle(Coordinate(left_wall_x, corridor_start), 1, corridor_width));
    }
}

void Tree::horizontal_z_shape_corridor(Node* origin, Node* end)
{
    Node* left_node;
    Node* right_node;

    if (origin->rectangle.origin.x < end->rectangle.origin.x) {
        left_node = origin;
        right_node = end;
    }
    else {
        right_node = end;
        left_node = origin;
    }

    // Ensures corridor won't be at the wall
    int wall_width = 1;

    int left_wall_start = left_node->room.top_right_corner().y + wall_width;
    int left_wall_end = left_node->room.bottom_right_corner().y - wall_width;
    int left_wall_x = left_node->room.bottom_right_corner().x;

    int right_wall_start = right_node->room.top_left_corner().y + wall_width;
    int right_wall_end = right_node->room.bottom_left_corner().y - wall_width;
    int right_wall_x = right_node->room.bottom_left_corner().x + wall_width;

    int corridor_width = (right_wall_x - left_wall_x);

    int random_start = rng.generate(left_wall_start, left_wall_end);
    int random_end = rng.generate(right_wall_start, right_wall_end);

    // Maybe create a z shape
    int first_section_width = corridor_width / 2;
    int second_section_width = corridor_width - first_section_width;
    corridors.push_back(Rectangle(Coordinate(left_wall_x, random_start), 1, first_section_width));
    corridors.push_back(Rectangle(Coordinate(right_wall_x - second_section_width, random_end), 1, second_section_width));

    int z_shape_start = min(random_start, random_end);
    corridors.push_back(Rectangle(Coordinate(left_wall_x + second_section_width - 1, z_shape_start), abs(random_start - random_end) + 1, 1));
}

Node* Tree::generate_corridors(Node* node) {
    if (!node->left->has_children() && !node->right->has_children()) {
        return generate_corridor(node->left, node->right);
    }
    else {
        Node* first_node = generate_corridors(node->left);
        Node* second_node = generate_corridors(node->right);

        return generate_corridor(first_node, second_node);
    }
}