#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "GGKP");
	loadTextures();
	
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	cam.pos = Vec2(300, 300);

	// Relative view
	sf::View view(sf::FloatRect(
		sf::Vector2f(cam.pos.x - w * 1 / cam.scale / 2, cam.pos.y - h * 1 / cam.scale / 2),
		sf::Vector2f(w * 1 / cam.scale, h * 1 / cam.scale)
	));
	view.setRotation((cam.dir * 180 / M_PI));
	window->setView(view);

	for (int i = 0; i < sys.landscape.size(); i++) {
		for (int j = 0; j < sys.landscape.size(); j++) {
			double alpha = sys.landscape[i][j] * 255 / 2;
			double limit = 1.3;

			Color col(100, 100, 255);

			if (sys.landscape[i][j] > limit)
				col = Color(100 + (sys.landscape[i][j] - limit) * 200, 255 - (sys.landscape[i][j] - limit) * 200, 100 - (sys.landscape[i][j] - limit) * 100);

			col.a = alpha;

			fillRect(i * sys.layers.cellSize, j * sys.layers.cellSize, sys.layers.cellSize, sys.layers.cellSize, col);
		}
	}

}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
