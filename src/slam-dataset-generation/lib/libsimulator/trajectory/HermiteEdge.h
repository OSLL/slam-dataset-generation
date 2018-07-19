#ifndef TRAJECTORY_HERMITEEDGE_H
#define TRAJECTORY_HERMITEEDGE_H

#include "math/PolynomialEdge.h"
#include "math/Pose.h"
#include <iostream>

class HermiteEdge : public PolynomialEdge<3> {
	public:
		HermiteEdge(const Pose & start_pose, const Pose & end_pose);
		HermiteEdge(const Vec & p1, const Vec & m1, const Vec & p2, const Vec & m2);
		void print(std::ostream & o = std::cout, int tabs = 0) const;
	private:

		static const double smoothing_factor;
};

#endif
