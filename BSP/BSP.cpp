// BSP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "Coordinate.h"
#include "Node.h"
#include "Tree.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

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

void debug_rectangle_areas(vector<vector<char>>& canvas, vector<Node*> leaves) {
    /*for (int i = 0; i < leaves.size(); i++)
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
    }*/

    for (int i = 0; i < leaves.size(); i++)
    {
        Rectangle current_rectangle = leaves[i]->room;

        for (int j = current_rectangle.origin.y; j < current_rectangle.origin.y + current_rectangle.height; j++)
        {
            for (int k = current_rectangle.origin.x; k < current_rectangle.origin.x + current_rectangle.width; k++)
            {
                if (j == current_rectangle.origin.y || k == current_rectangle.origin.x || j == current_rectangle.origin.y + current_rectangle.height - 1 || k == current_rectangle.origin.x + current_rectangle.width - 1) {
                    canvas[j][k] = '#';
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
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    int height = 60;
    int width = 180;

    Tree tree(Node(Rectangle(Coordinate(0, 0), height, width)));

    tree.partition(&tree.root, 0, 3);

    vector<Node*> leaves;

    collect_leaves(&tree.root, leaves);

    //generate_room_for_leaves(leaves);

    vector<vector<char>> canvas(height, vector<char>(width, ' '));

    debug_rectangle_areas(canvas, leaves);
    debug_rectangles(leaves);
    cout << endl;
    draw_canvas(canvas);
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    duration<double, std::milli> ms_double = t2 - t1;

    cout << ms_int.count() << "ms\n";
    cout << ms_double.count() << "ms\n";
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
