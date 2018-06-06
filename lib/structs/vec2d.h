#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

class Vec2D {
	public:
		Vec2D(double x_val, double y_val) : x(x_val), y(y_val) {}
		double x;
		double y;
};

std::ostream & operator<<(std::ostream & o, Vec2D v);

#endif
