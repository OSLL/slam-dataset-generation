#ifndef ROBOT_H
#define ROBOT_H

#include "world/world.h"
#include "trajectory/trajectory.h"
#include "misc/pose.h"

class Robot {
	private:
		// References to 
		const World & world;
		const Trajectory & trajectory;

		Pose current_pose;
	public:
		Robot(const World & world_val, const Trajectory & trajectory_val);

		void change_theta;
};

#endif
