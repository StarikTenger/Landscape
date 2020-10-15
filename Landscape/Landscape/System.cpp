#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

System::System() {
	layers = Layers(100, 5, 6, 100, 2);
	landscape = generateLandscape();
}

System::~System() {
}

std::vector<std::vector<double>> System::generateLandscape() {
	int len = layers.len;
	std::vector<std::vector<double>> landscape(len);
	for (auto& line : landscape)
		line = std::vector<double>(len);

	std::vector<std::vector<std::vector<double>>> heightLayers;

	double currentSize = layers.initialSize;
	double currentAmplitude = 1;

	for (int i = 0; i < layers.layers.size(); i++) {

		std::vector<std::vector<double>> layer(len);
		for (int x = 0; x < len; x++) {
			layer[x] = std::vector<double>(len);
			for (int y = 0; y < len; y++) {
				int x0 = (int)(x * layers.cellSize / currentSize);
				int y0 = (int)(y * layers.cellSize / currentSize);
				double top = additionalMath::interpolateCubic(layers.layers[i][x0][y0].value(), layers.layers[i][x0 + 1][y0].value(),
					x * layers.cellSize / currentSize - x0);
				double bottom = additionalMath::interpolateCubic(layers.layers[i][x0][y0 + 1].value(), layers.layers[i][x0 + 1][y0 + 1].value(),
					x * layers.cellSize / currentSize - x0);
				layer[x][y] = additionalMath::interpolateCubic(top, bottom,
					y * layers.cellSize / currentSize - y0) * currentAmplitude;
			}
		}

		heightLayers.push_back(layer);
		currentSize /= layers.ratio;
		currentAmplitude /= layers.ratio;
	}

	for (auto& line : landscape)
		for (auto& h : line)
			h = 0;

	for (int i = 0; i < heightLayers.size(); i++)
		for (int x = 0; x < len; x++)
			for (int y = 0; y < len; y++)
				landscape[x][y] += heightLayers[i][x][y];

	return landscape;
}

