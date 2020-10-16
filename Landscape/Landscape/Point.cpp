#include "Point.h"
#include "math.h"

Point::Point() {}
void Point::calculateValue() {
	value =  0.5 + sin(phase * freq) * 0.5;
}