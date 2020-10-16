#include "Config.h"

std::stringstream Config::comment(std::ifstream& file) {
	std::stringstream newFile; // file without comments
	std::string elem; // current input

	while (file >> elem) {
		if (elem == "#") { // Comment
			std::string input = "";
			std::getline(file, input);
		}
		else {
			newFile << elem << " ";
		}
	}
	return newFile;
}

void Config::loadFromFile(std::string path) {
	std::ifstream file(path);
	std::stringstream input = comment(file);
	file.close();
	std::string command;
	while (input >> command) {
		if (command == "LEVELS")
			input >> levels;
		if (command == "INITIAL_SIZE")
			input >> initialSize;
		if (command == "RATIO")
			input >> ratio;
		if (command == "THRESHOLD")
			input >> threshold;
	}
}

