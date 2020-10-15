#include "geometry.h"
#include "System.h"
#include "random.h"
#include <iostream>
#include <math.h>

void System::step() {
	double currentSize = layers.initialSize;
	for (int i = 0; i < layers.layers.size(); i++) {
		int k = (int)(mouse.x / currentSize);
		for (int j = 0; j < layers.layers[i].size(); j++) {
			double x = j * currentSize;
			
			if (abs(x - mouse.x) > 50 && !(j == k || j == k + 1))
				layers.layers[i][j].phase += dt * 0.001 * (abs(x - mouse.x) - 50) / 500;
		}
		currentSize /= layers.ratio;
	}

	landscape = generateLandscape();
}