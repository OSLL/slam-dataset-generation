#include "math/Pose.h"

using std::ostream;

Pose::Pose(const Vec & pos_val, const double & theta_val) :
	pos(pos_val),
	theta(theta_val)
{ }

void Pose::print(ostream & o, int tabs) const {
	o << "Pose: pos = " << pos << ", theta = " << theta;
}

// For ability to be sorted in an std::sort
bool Pose::operator<(const Pose & p) const {
	if (pos.x != p.pos.x) {
		return pos.x < p.pos.x;
	} else if (pos.y != p.pos.y) {
		return pos.y < p.pos.y;
	} else {
		return theta < p.theta;
	}
}

ostream & operator<<(ostream & o, const Pose & p) {
	p.print();
	return o;
}
