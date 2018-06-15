#include "ray.h"
#include <cmath>

Ray::Ray(const Vec & start_point, const double & direction_angle) :
	start(start_point)
{
	double x = cos(direction_angle);
	double y = sin(direction_angle);

	direction = {x, y};
}
