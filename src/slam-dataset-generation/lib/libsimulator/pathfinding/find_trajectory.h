#ifndef FINDTRAJECTORY_H
#define FINDTRAJECTORY_H

#include <vector>
#include "world/World.h"
#include "path/non_observable/Trajectory.h"

Trajectory find_trajectory(World & world, const std::vector<Pose> & critical_poses);

#endif