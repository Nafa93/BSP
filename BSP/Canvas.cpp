#include "Canvas.h"

#include <iostream>

using namespace std;

void Canvas::draw()
{
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            cout << data[i][j];
        }
        cout << endl;
    }
}

void Canvas::add_rectangles(vector<Rectangle> rectangles, char character)
{
    for (int i = 0; i < rectangles.size(); i++)
    {
        for (int j = rectangles[i].origin.y; j < rectangles[i].origin.y + rectangles[i].height; j++)
        {
            for (int k = rectangles[i].origin.x; k < rectangles[i].origin.x + rectangles[i].width; k++)
            {
                if (j == rectangles[i].origin.y || k == rectangles[i].origin.x || j == rectangles[i].origin.y + rectangles[i].height - 1 || k == rectangles[i].origin.x + rectangles[i].width - 1) {
                    if (data[j][k] == ' ') {
                        data[j][k] = character;
                    }
                }
                else {
                    data[j][k] = ' ';
                }
            }
        }
    }
}

void Canvas::add_corridors(vector<Rectangle> rectangles, char character)
{
    for (int i = 0; i < rectangles.size(); i++)
    {
        for (int j = rectangles[i].origin.y; j < rectangles[i].origin.y + rectangles[i].height; j++)
        {
            for (int k = rectangles[i].origin.x; k < rectangles[i].origin.x + rectangles[i].width; k++)
            {
                if (j == rectangles[i].origin.y || k == rectangles[i].origin.x || j == rectangles[i].origin.y + rectangles[i].height - 1 || k == rectangles[i].origin.x + rectangles[i].width - 1) {
                    data[j][k] = character;
                }
            }
        }
    }
}
