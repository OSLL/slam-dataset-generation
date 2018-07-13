#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include "math/Pose.h"
#include "trajectory/HermitePath.h"

class Trajectory : public HermitePath {
	public:
		Trajectory(std::vector<Pose> intermediate_poses);

		Pose begin() const;
		Pose end() const;
};

#endif
