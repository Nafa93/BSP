#pragma once

#include "Rectangle.h"

#include <vector>

using namespace std;

class Canvas
{
public:
	Canvas(int height, int width): height(height), width(width), data(vector<vector<char>>(height, vector<char>(width, ' '))) { }
	void draw();
	void add_rectangles(vector<Rectangle> rectangles);
private:
	vector<vector<char>> data;
	int height;
	int width;
};

