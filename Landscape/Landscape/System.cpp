#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

System::System() {
	layers = Layers(600, 7, 1, 300, 2);
	landscape = generateLandscape();
}

System::~System() {
}

std::vector<double> System::generateLandscape() {
	int len = layers.len;
	std::vector<double> landscape(len);

	std::vector<std::vector<double>> heightLayers;

	double currentSize = layers.initialSize;
	double currentAmplitude = 600;

	for (int i = 0; i < layers.layers.size(); i++) {

		std::vector<double> layer(len);
		for (int j = 0; j < len; j++) {
			int k = (int)(j * layers.cellSize / currentSize);
			layer[j] =  additionalMath::interpolateCubic(layers.layers[i][k].value(), layers.layers[i][k + 1].value(),
				j * layers.cellSize / currentSize - k) * currentAmplitude;
		}

		heightLayers.push_back(layer);
		currentSize /= layers.ratio;
		currentAmplitude /= layers.ratio;
	}

	for (auto& h : landscape)
		h = 0;

	for (int i = 0; i < heightLayers.size(); i++)
		for (int j = 0; j < len; j++)
			landscape[j] += heightLayers[i][j];

	return landscape;
}

