#ifndef TRAJECTORY_TRAJECTORY_H
#define TRAJECTORY_TRAJECTORY_H

#include <vector>
#include <iostream>
#include "math/Pose.h"
#include "trajectory/HermitePath.h"

class Trajectory : public HermitePath {
	public:
		Trajectory(std::vector<Pose> intermediate_poses);
		virtual void print(std::ostream & o = std::cout, int tabs = 0) const override;
};

#endif
