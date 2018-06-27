#include "trajectory/trajectory.h"
#include <vector>
#include <cmath>

using std::vector;

Trajectory::Trajectory(vector<Pose> intermediate_poses) :
	HermitePath(intermediate_poses)
{
	// Modify the SplinePath so that velocity is constant
}
