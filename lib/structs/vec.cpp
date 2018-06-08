#include "structs/vec2d.h"

using std::ostream;

Vec::Vec(double x_val, double y_val) :
	x(x_val),
	y(y_val)
{
	//
}

ostream & operator<<(ostream & o, Vec v) {
	printf("(%.2f, %.2f)", v.x, v.y);
	return o;
}
