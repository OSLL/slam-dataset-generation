#include "trajectory/Trajectory.h"
#include <vector>
#include <cmath>

using std::vector;

Trajectory::Trajectory(vector<Pose> intermediate_poses) :
	HermitePath(intermediate_poses)
{
	// Modify the SplinePath so that velocity is constant
}

Pose Trajectory::begin() const {
	return (*this)(0);
}

Pose Trajectory::end() const {
	return (*this)(edges.size() + 1);
}
