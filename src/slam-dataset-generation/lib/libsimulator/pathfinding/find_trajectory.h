#ifndef FINDTRAJECTORY_H
#define FINDTRAJECTORY_H

#include <vector>
#include "world/world.h"
#include "trajectory/trajectory.h"

Trajectory find_trajectory(World & world, const std::vector<Pose> & critical_poses);

#endif
