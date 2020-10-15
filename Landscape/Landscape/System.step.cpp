#include "geometry.h"
#include "System.h"
#include "random.h"
#include <iostream>
#include <math.h>

void System::step() {
	/*double currentSize = layers.initialSize;
	for (int i = 0; i < layers.layers.size(); i++) {
		int k = (int)(mouse.x / currentSize);
		for (int j = 0; j < layers.layers[i].size(); j++) {
			double x = j * currentSize;
			
			if (abs(x - mouse.x) > 50 && !(j == k || j == k + 1))
				layers.layers[i][j].phase += dt * 0.001 * (abs(x - mouse.x) - 50) / 500;
		}
		currentSize /= layers.ratio;
	}*/

	double currentSize = layers.initialSize;
	for (int i = 0; i < layers.layers.size(); i++) {
		int xM = (int)(mouse.x / currentSize);
		int yM = (int)(mouse.y / currentSize);
		for (int x = 0; x < layers.layers[i].size(); x++) {
			for (int y = 0; y < layers.layers[i][x].size(); y++) {
				//layers.layers[i][x][y].phase += dt * 0.6;
				double x0 = x * currentSize;
				double y0 = y * currentSize;

				double dist = geom::distance(Vec2(x0, y0), mouse);
				double lim = 50;
				if (dist > lim && !(x == xM || x == xM + 1) && !(y == yM || y == yM + 1))
					layers.layers[i][x][y].phase += dt * 0.5 * (dist - lim) / 300;
			}
		}
		currentSize /= layers.ratio;
	}

	landscape = generateLandscape();
}