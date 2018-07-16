#ifndef TRAJECTORY_HERMITEEDGE_H
#define TRAJECTORY_HERMITEEDGE_H

#include "math/PolynomialEdge.h"
#include "math/Pose.h"

class HermiteEdge : public PolynomialEdge<3> {
	public:
		HermiteEdge(const Pose & start_pose, const Pose & end_pose);
	private:
		HermiteEdge(const Vec & p1, const Vec & m1, const Vec & p2, const Vec & m2);

		const double smoothing_factor = 0.2f;
};

#endif
