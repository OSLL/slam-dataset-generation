#include "ray.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

Ray::Ray(const Vec & start_point, const double & theta_val) :
	ObservationPath(start_point, {0, 0}, on_ray),
	theta(theta_val)
{
	update_end();
}

void Ray::update_end() {
	double x = start.x + cos(theta);
	double y = start.y + sin(theta);
	end = {x, y};
}

void Ray::update_theta() {
	Vec dir = end - start;
	theta = atan2(dir.y, dir.x);
}

void Ray::change_theta(double dtheta) {
	theta += dtheta;
	update_end();
}

bool Ray::on_ray(const Vec & p, const ObservationPath & op) {

	Vec s_to_p = p - op.start;
	Vec s_to_e = op.end - op.start;

	return s_to_p.dot(s_to_e) >= 0;
}

void Ray::print(ostream & o, int tabs) const {
	// Print the corret number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "Ray: " << start << " -> " << end << ", theta = " << theta;
}
