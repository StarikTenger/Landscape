#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "Config.h"



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Dynamic Landscape", sf::Style::Close);
	loadTextures();
	sf::Texture *tex = new sf::Texture;
	textures["render"] = tex;
}

void DrawSystem::loadGrid() {
	System& sys = *system;
	gridImg.create(sys.landscape.size(), sys.landscape.size());

	
	for (int x = 0; x < sys.landscape.size(); x++) {
		for (int y = 0; y < sys.landscape.size(); y++) {
			gridImg.setPixel(x, y, sf::Color(0, 0, 0, 0));
		}
	}

	double alpha = 255;
	double currentSize = (int)sys.layers.initialSize;
	double threshold = 0.9 / sys.layers.initialSize;
	for (int i = 0; i < sys.layers.layers.size(); i++) {
		for (int x = 0; x < sys.landscape.size(); x++) {
			for (int y = 0; y < sys.landscape.size(); y++) {
				if ((x / currentSize - (int)(x / currentSize)) < threshold ||
					(y / currentSize - (int)(y / currentSize)) < threshold) {
					Color col(255, 255, 255);
					gridImg.setPixel(x, y, sf::Color(col.r, col.g, col.b, std::max(alpha, (double)gridImg.getPixel(x, y).a)));
				}
			}
		}

		currentSize /= sys.layers.ratio;
		alpha /= sys.layers.ratio;
		threshold *= sys.layers.ratio;
	}

	sf::Texture* grid = new sf::Texture;
	grid->loadFromImage(gridImg);
	textures["grid"] = grid;
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


	sf::Image render;
	render.create(sys.landscape.size(), sys.landscape.size());
	for (int x = 0; x < sys.landscape.size(); x++) {
		for (int y = 0; y < sys.landscape.size(); y++) {
			double limit = 1.3;

			Color col(100, 100, 255);

			if (sys.landscape[x][y] > limit)
				col = Color(100 + (sys.landscape[x][y] - limit) * 200, 255 - (sys.landscape[x][y] - limit) * 200, 100 - (sys.landscape[x][y] - limit) * 100);

			// Pixel on map
			col = getCol(sys.landscape[x][y] / sys.layers.maxVal, config->threshold);
			render.setPixel(x, y, sf::Color(col.r, col.g, col.b, col.a));

			// Pixel on grid
			auto alpha = gridImg.getPixel(x, y).a;
			col = Color(255, 255, 255) - col;
			gridImg.setPixel(x, y, sf::Color(col.r, col.g, col.b, alpha));
		}
	}

	
	textures["render"]->loadFromImage(render);
	image("render", 300, 300, 600, 600, 0);
	textures["grid"]->loadFromImage(gridImg);
	image("grid", 300, 300, 600, 600, 0);
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
