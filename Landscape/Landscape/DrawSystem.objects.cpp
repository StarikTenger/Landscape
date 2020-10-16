#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

Color DrawSystem::getCol(double val, double threshold) {
	if (val < threshold)
		return Color(50, 50, 150);
	if (val < threshold + 0.2 * (1 - threshold))
		return Color(140, 189, 156);
	if (val < threshold + 0.5 * (1 - threshold))
		return Color(181, 222, 140);
	if (val < threshold + 0.8 * (1 - threshold))
		return Color(255, 255, 120);
	return Color(170, 110, 80);
}