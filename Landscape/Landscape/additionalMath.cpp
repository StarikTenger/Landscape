#include "additionalMath.h"

double additionalMath::interpolateCubic(double left, double right, double val) {
	val = (-2 * val * val * val + 3 * val * val);
	//val = val > 0.5 ? 1 : 0;
	return  left + (right - left) * val;
}