#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

class Vec {
	private:
	public:
		Vec(double x_val = -1.0, double y_val = -1.0);
		double x;
		double y;
		Vec operator+(const Vec & v) const;
		bool operator==(const Vec & v) const;
		bool operator!=(const Vec & v) const;
};

std::ostream & operator<<(std::ostream & o, Vec v);

// Null vector returned whenever a valid vector could not be found
extern const Vec null_vector;

#endif
