#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

Color DrawSystem::getCol(double val) {
	val += 0.2;
	if (val < 1.3)
		return Color(50, 50, 150);
	if (val < 1.35)
		return Color(140, 189, 156);
	if (val < 1.6)
		return Color(181, 222, 140);
	if (val < 1.9)
		return Color(255, 255, 120);
	return Color(170, 110, 80);
}