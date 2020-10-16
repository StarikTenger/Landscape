#pragma once
#include <vector>
#include <fstream>
#include "geometry.h"
#include "additionalMath.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Layers.h"

class System {
public:
	double dt = 0.02;
	Layers layers;
	std::vector<std::vector<double>> landscape;

	Vec2 mouse;
	int mode = 0;

	System();
	~System();

	std::vector<std::vector<double>> generateLandscape();

	void step();
};