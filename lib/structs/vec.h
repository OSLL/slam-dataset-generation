#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

class Vec {
	private:
	public:
		Vec(double x_val, double y_val);
		double x;
		double y;
};

std::ostream & operator<<(std::ostream & o, Vec v);

#endif
