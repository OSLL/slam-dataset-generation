#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include "misc/pose.h"
#include "trajectory/hermitepath.h"

class Trajectory : public HermitePath {
	public:
		Trajectory(std::vector<Pose> intermediate_poses);
};

#endif
