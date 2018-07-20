#include "trajectory/Trajectory.h"
#include <vector>
#include <cmath>

using std::vector;

#include <iostream>
using std::cout;
using std::endl;

Trajectory::Trajectory(vector<Pose> intermediate_poses) :
	HermitePath(intermediate_poses)
{ }
