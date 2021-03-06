#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Config.h"

Control::Control() {
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));

		}
	}
	
	config.loadFromFile("config.conf");

	sys = System(&config);
	drawSys.config = &config;

	sys.generateLandscape();
	drawSys.system = &sys;
	drawSys.loadGrid();
}

Control::~Control() {

}

Vec2 Control::getCursorPos() {
	return geom::rotate((mouse.pos - drawSys.cam.border/2) / drawSys.cam.scale, drawSys.cam.angle);
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;

		events();
		drawSys.mouse = mouse;

		sys.mouse = mouse.pos;
		sys.mode = mouse.state;

		for (int i = 0; i < 1; i++) {
			sys.step();
		}

		drawSys.system = &sys;
		drawSys.draw();
		drawSys.window->display();

		
	}
}
