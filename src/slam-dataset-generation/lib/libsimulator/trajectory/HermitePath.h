#ifndef HERMITEPATH_H
#define HERMITEPATH_H

#include <vector>
#include "trajectory/HermiteEdge.h"
#include "math/Pose.h"

class HermitePath {
	protected:
		std::vector<HermiteEdge> edges;
	public:
		HermitePath(const std::vector<Pose> & intermediate_poses);
		
		double t_min() const;
		double t_max() const;

		Pose operator()(double t) const;
};

#endif
