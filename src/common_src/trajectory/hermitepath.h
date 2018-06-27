#ifndef HERMITEPATH_H
#define HERMITEPATH_H

#include <vector>
#include "trajectory/hermiteedge.h"
#include "misc/pose.h"

class HermitePath {
	protected:
		std::vector<HermiteEdge> edges;
	public:
		HermitePath(const std::vector<Pose> & intermediate_poses);
		
		double t_min() {return 0.0f;}
		double t_max() {return (double)edges.size() + 1.0f;}

		Pose operator()(double t);
};

#endif
