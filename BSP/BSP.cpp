// BSP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "Coordinate.h"
#include "Node.h"
#include "Tree.h"
#include "Canvas.h"
#include "ExecutionMeasurer.h"

using namespace std;

int main()
{
    ExecutionMeasurer measurer;

    measurer.start();

    int height = 60;
    int width = 180;

    Tree tree(Node(Rectangle(Coordinate(0, 0), height, width)));

    tree.partition(&tree.root, 0, 3);

    tree.generate_corridors(&tree.root);

    Canvas canvas(height, width);
    
    canvas.add_corridors(tree.corridors, '.');
    
    canvas.add_rectangles(tree.rooms, '#');

    canvas.draw();

    measurer.stop();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
