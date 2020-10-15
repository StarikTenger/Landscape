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
	std::vector<double> landscape;

	Vec2 mouse;

	System();
	~System();

	std::vector<double> generateLandscape();

	void step();
};