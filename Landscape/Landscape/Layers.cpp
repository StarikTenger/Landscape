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
	
	double currentSize = initialSize;
	double freqCoeff = 1;

	for (int i = 0; i < levels; i++) {
		std::vector<Point> anchorPoints((int)(len * cellSize / currentSize) + 1);

		for (auto& p : anchorPoints) {
			p.freq = random::floatRandom(1, 3, 4) * freqCoeff;
			p.phase = random::floatRandom(0, 1, 4) * 2 * M_PI / p.freq;
		}

		layers.push_back(anchorPoints);
		currentSize /= ratio;
		freqCoeff *= ratio;
	}
}
