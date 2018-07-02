#ifndef FINDTRAJECTORY_H
#define FINDTRAJECTORY_H

#include "pathfinding/find_critical_poses.h"
#include "trajectory/trajectory.h"

Trajectory find_trajectory(World & world, const critical_poses_t & critical_poses);

#endif
