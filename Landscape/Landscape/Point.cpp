#include "Point.h"
#include "math.h"

Point::Point() {}
double Point::value() {
	return 0.5 + sin(phase * freq) * 0.5;
}