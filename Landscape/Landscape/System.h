#pragma once
#include <vector>
#include <fstream>
#include "geometry.h"
#include <string>
#include <SFML/Graphics.hpp>

class System {
	double interpolate(double left, double right, double val);

public:
	double dt = 0.02;
	double cellSize = 1;
	std::vector<double> landscape;

	System();
	~System();

	std::vector<double> generateLandscape(int len, int levels, double initialSize, double ratio);

	void step();
};