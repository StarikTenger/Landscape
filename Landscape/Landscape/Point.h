#pragma once
class Point {
public:
	double freq = 1;
	double phase = 0;
	double value = 0;

	Point();
	void calculateValue();
};

