#include "geometry.h"
#include "System.h"
#include "random.h"
#include <iostream>
#include <algorithm>
#include <math.h>

void System::step() {

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
				double lim = 10;
				if (!mode || dist > lim && !(x == xM || x == xM + 1) && !(y == yM || y == yM + 1))
					layers.layers[i][x][y].phase += dt * 0.5 * (dist - lim) / 300 ;
				layers.layers[i][x][y].calculateValue();
			}
		}
		currentSize /= layers.ratio;
	}

	landscape = generateLandscape();
}