#pragma once
#include <string>
#include <fstream>
#include <sstream>

class Config {
public:
	int levels = 5;

	double initialSize = 100;
	double ratio = 2;
	double threshold = 0.5;

	std::stringstream comment(std::ifstream& file);
	void loadFromFile(std::string);
};

