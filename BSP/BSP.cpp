// BSP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Coordinate
{
public:
    Coordinate(int x, int y) : x(x), y(y) {};
    int x;
    int y;
};

class Rectangle
{
public:
    Rectangle(Coordinate origin, int height, int width) : origin(origin), height(height), width(width) {};
    Coordinate origin;
    int height;
    int width;
};

class Node
{
public:
    Node(Rectangle rectangle) : rectangle(rectangle), room(rectangle), left(nullptr), right(nullptr) {};
    Rectangle rectangle;
    Rectangle room;
    Node* left;
    Node* right;
};


void partition(Node* node, int depth, int max_depth) {
    if (depth == max_depth) {
        return;
    }

    random_device rd;
    mt19937 gen(rd());

    bool vertical = depth % 2 == 0;

    if (vertical) {

        int half_height = node->rectangle.height / 2;
        int percent_height = node->rectangle.height * 20 / 100;
        uniform_int_distribution<> height_threshold(half_height - percent_height, half_height + percent_height);
        int random_height = height_threshold(gen);

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
        uniform_int_distribution<> width_threshold(half_width - percent_width, half_width + percent_width);
        int random_width = width_threshold(gen);

        Rectangle left_rectangle(node->rectangle.origin, node->rectangle.height, random_width);
        Rectangle right_rectangle(Coordinate(node->rectangle.origin.x + random_width, node->rectangle.origin.y), node->rectangle.height, node->rectangle.width - random_width);

        node->left = new Node(left_rectangle);
        node->right = new Node(right_rectangle);

        partition(node->left, depth + 1, max_depth);
        partition(node->right, depth + 1, max_depth);
    }
}

void collect_leaves(Node* root, vector<Node*>& leaves) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        leaves.push_back(root);
    }
    else {
        if (root->left != nullptr) {
            collect_leaves(root->left, leaves);
        }
        if (root->right != nullptr) {
            collect_leaves(root->right, leaves);
        }
    }
}

void generate_room_for_leaves(vector<Node*>& leaves) {
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < leaves.size(); i++)
    {
        int half_height = leaves[i]->rectangle.height / 2;
        int percent_height = leaves[i]->rectangle.height * 20 / 100;
        uniform_int_distribution<> height_threshold(half_height - percent_height, half_height + percent_height);
        int random_height = height_threshold(gen);

        int half_width = leaves[i]->rectangle.width / 2;
        int percent_width = leaves[i]->rectangle.width * 20 / 100;
        uniform_int_distribution<> width_threshold(half_width - percent_width, half_width + percent_width);
        int random_width = width_threshold(gen);


        uniform_int_distribution<> x_threshold(leaves[i]->rectangle.origin.x + 1, leaves[i]->rectangle.origin.x + leaves[i]->rectangle.width - random_width - 1);
        uniform_int_distribution<> y_threshold(leaves[i]->rectangle.origin.y + 1, leaves[i]->rectangle.origin.y + leaves[i]->rectangle.height - random_height - 1);
        int random_x = x_threshold(gen);
        int random_y = y_threshold(gen);

        leaves[i]->room = Rectangle(Coordinate(random_x, random_y), random_height, random_width);
    }
}

void debug_rectangle_areas(vector<vector<char>>& canvas, vector<Node*> leaves) {
    
    vector<char> alphabet = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', '!', '@', '#', '$'
    };


    for (int i = 0; i < leaves.size(); i++)
    {
        Rectangle current_rectangle = leaves[i]->rectangle;

        for (int j = current_rectangle.origin.y; j < current_rectangle.origin.y + current_rectangle.height; j++)
        {
            for (int k = current_rectangle.origin.x; k < current_rectangle.origin.x + current_rectangle.width; k++)
            {
                if (j == current_rectangle.origin.y || k == current_rectangle.origin.x || j == current_rectangle.origin.y + current_rectangle.height - 1 || k == current_rectangle.origin.x + current_rectangle.width - 1) {
                    canvas[j][k] = alphabet[i];
                }
            }
        }
    }

    for (int i = 0; i < leaves.size(); i++)
    {
        Rectangle current_rectangle = leaves[i]->room;

        for (int j = current_rectangle.origin.y; j < current_rectangle.origin.y + current_rectangle.height; j++)
        {
            for (int k = current_rectangle.origin.x; k < current_rectangle.origin.x + current_rectangle.width; k++)
            {
                if (j == current_rectangle.origin.y || k == current_rectangle.origin.x || j == current_rectangle.origin.y + current_rectangle.height - 1 || k == current_rectangle.origin.x + current_rectangle.width - 1) {
                    canvas[j][k] = alphabet[i];
                }
            }
        }
    }
}

void draw_canvas(vector<vector<char>> canvas) {
    for (int i = 0; i < canvas.size(); i++)
    {
        for (int j = 0; j < canvas[i].size(); j++)
        {
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

void debug_rectangles(vector<Node*> leaves) {
    for (int i = 0; i < leaves.size(); i++)
    {
        printf("Rectangle n%d origin x: %d origin y: %d height: %d width: %d", i + 1, leaves[i]->rectangle.origin.x, leaves[i]->rectangle.origin.y, leaves[i]->rectangle.height, leaves[i]->rectangle.width);
        cout << endl;
    }
}

int main()
{
    int height = 72;
    int width = 240;

    Rectangle rectangle(Coordinate(0, 0), height, width);

    Node node(rectangle);

    partition(&node, 0, 3);

    vector<Node*> leaves;

    collect_leaves(&node, leaves);

    generate_room_for_leaves(leaves);

    vector<vector<char>> canvas(height, vector<char>(width, ' '));

    debug_rectangle_areas(canvas, leaves);
    debug_rectangles(leaves);
    cout << endl;
    draw_canvas(canvas);
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
