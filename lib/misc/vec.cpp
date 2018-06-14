#include "misc/vec.h"

using std::ostream;

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
	return (x == v.x) && (y == v.y);
}

bool Vec::operator!=(const Vec & v) const {
	return (x != v.x) || (y != v.y);
}

ostream & operator<<(ostream & o, Vec v) {
	printf("(%.2f, %.2f)", v.x, v.y);
	return o;
}
