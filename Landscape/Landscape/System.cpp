#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

double System::interpolate(double left, double right, double val) {
	return  left + (right - left) * (-2 * val * val * val + 3 * val * val);
}

System::System() {
	landscape = generateLandscape(600, 3, 300, 2);
}

System::~System() {
}

std::vector<double> System::generateLandscape(int len, int levels, double initialSize, double ratio) {
	std::vector<double> landscape(len);

	std::vector<std::vector<double>> layers;

	double currentSize = initialSize;
	double currentAmplitude = 500;

	for (int i = 0; i < levels; i++) {
		std::vector<double> anchorPoints((int)(len * cellSize / currentSize) + 1);

		for (auto& h : anchorPoints)
			h = random::floatRandom(0, currentAmplitude, 2);

		std::vector<double> layer(len);
		for (int j = 0; j < len; j++) {
			int k = (int)(j * cellSize / currentSize);
			layer[j] =  interpolate(anchorPoints[k], anchorPoints[k + 1], j * cellSize / currentSize - k);
		}

		layers.push_back(layer);
		currentSize /= ratio;
		currentAmplitude /= ratio;
	}

	for (auto& h : landscape)
		h = 0;

	for (int i = 0; i < levels; i++)
		for (int j = 0; j < len; j++)
			landscape[j] += layers[i][j];

	return landscape;
}

