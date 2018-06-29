#ifndef FIND_CRITICAL_POSES_H
#define FIND_CRITICAL_POSES_H

#include <set>
#include "world/world.h"
#include "misc/pose.h"

typedef std::set<Pose> critical_poses_t;

critical_poses_t find_critical_poses(const World & world);

#endif
