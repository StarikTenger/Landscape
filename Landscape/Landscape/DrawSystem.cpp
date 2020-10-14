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

	fillRect(0, 0, 100, 10, Color(255, 255, 255));

	for (int i = 0; i < sys.landscape.size(); i++) {
		fillRect(i * sys.cellSize, 0, sys.cellSize, sys.landscape[i], Color(255, 255, 255));
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
