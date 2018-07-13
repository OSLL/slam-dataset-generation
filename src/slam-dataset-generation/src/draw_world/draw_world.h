#ifndef DRAW_WORLD_H
#define DRAW_WORLD_H

#include "world/World.h"
#include "path/non_observable/Trajectory.h"

void draw_world(const World & world, const char * filename);
void draw_trajectory(const World & world, const Trajectory & trajectory, const char * filename);
void draw_world_and_trajectory(const World & world, const Trajectory & trajectory, const char * filename);

#endif