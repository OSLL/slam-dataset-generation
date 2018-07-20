#ifndef TRAJECTORY_TRAJECTORY_H
#define TRAJECTORY_TRAJECTORY_H

#include <vector>
#include "math/Pose.h"
#include "trajectory/HermitePath.h"

class Trajectory : public HermitePath {
	public:
		Trajectory(std::vector<Pose> intermediate_poses);
};

#endif
