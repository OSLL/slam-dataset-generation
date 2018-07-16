#ifndef PATHFINDING_FIND_TRAJECTORY_H
#define PATHFINDING_FIND_TRAJECTORY_H

#include <vector>
#include "world/World.h"
#include "trajectory/Trajectory.h"

Trajectory find_trajectory(World & world, const std::vector<Pose> & critical_poses);

#endif
