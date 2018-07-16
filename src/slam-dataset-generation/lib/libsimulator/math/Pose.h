#ifndef MATH_POSE_H
#define MATH_POSE_H

#include <iostream>
#include "math/Vec.h"

class Pose {
	public:
		Pose(const Vec & pos_val, const double & theta_val);
		Vec pos;
		double theta;

		void print(std::ostream & o = std::cout, int tabs = 0) const;

		bool operator<(const Pose & p) const;
};

std::ostream & operator<<(std::ostream & o, const Pose & p);

#endif
