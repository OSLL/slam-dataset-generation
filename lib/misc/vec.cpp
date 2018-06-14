#include "misc/vec.h"
#include <iostream>
#include <cmath>

using std::ostream;
using std::cout;
using std::endl;

// Null vector returned whenever a valid vector could not be found
const Vec null_vector {0, 0};

Vec::Vec(double x_val, double y_val) :
	x(x_val),
	y(y_val)
{
	//
}

Vec Vec::operator+(const Vec & v) const {
	return {x + v.x, y + v.y};
}

bool Vec::operator==(const Vec & v) const {
	double dx = abs(v.x - x);
	double dy = abs(v.y - y);

	const double epsilon = 0.05;

	return (dx < epsilon) && (dy < epsilon);
}

bool Vec::operator!=(const Vec & v) const {
	return !(*this == v);
}

ostream & operator<<(ostream & o, Vec v) {
	printf("(%.2f, %.2f)", v.x, v.y);
	return o;
}
