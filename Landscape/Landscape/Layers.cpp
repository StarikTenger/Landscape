#include "Layers.h"
#include "random.h"
#include "geometry.h"

Layers::Layers(){}

Layers::Layers(int _len, int levels, double _cellSize, double _initialSize, double _ratio) {
	layers = {};
	len = _len;
	cellSize = _cellSize;
	initialSize = _initialSize;
	ratio = _ratio;
	maxVal = 0;
	
	double currentSize = initialSize;
	double freqCoeff = 1;

	for (int i = 0; i < levels; i++) {
		int currentLen = ceil(len * cellSize / currentSize) + 1;
		std::vector<std::vector<Point>> anchorPoints(currentLen);

		for (auto& line : anchorPoints) {
			line = std::vector<Point>(currentLen);
			for (auto& p : line) {
				p.freq = random::floatRandom(1, 3, 4) * freqCoeff;
				p.phase = random::floatRandom(0, 1, 4) * 2 * M_PI / p.freq;
			}			
		}

		layers.push_back(anchorPoints);
		currentSize /= ratio;
		maxVal += 1.0 / freqCoeff;
		freqCoeff *= ratio;
	}
}
