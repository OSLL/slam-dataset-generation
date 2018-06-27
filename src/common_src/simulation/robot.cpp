#include "simulation/robot.h"

Robot::Robot(const World & world_val, const Trajectory & trajectory_val) :
	world(world_val),
	trajectory(trajectory_val)
{ }
