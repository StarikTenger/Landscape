#pragma once
#include "Point.h"
#include <vector>

class Layers {
public:
	int len = 0;
	double initialSize = 300;
	double ratio = 2;
	double cellSize = 1;
	std::vector<std::vector<std::vector<Point>>> layers;
	Layers();
	Layers(int _len, int levels, double _cellSize, double _initialSize, double _ratio);
};

