// BSP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "Coordinate.h"
#include "Node.h"
#include "Tree.h"
#include "Canvas.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

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

    Canvas canvas(height, width);

    canvas.add_rectangles(tree.rooms);

    canvas.add_rectangles(tree.areas);

    canvas.draw();

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
