#ifndef RAY_H
#define RAY_H

#include "misc/vec.h"

class Ray {
	public:
		Vec start;
		Vec direction;

		Ray(const Vec & start_point, const double & direction_angle);
};

#endif
