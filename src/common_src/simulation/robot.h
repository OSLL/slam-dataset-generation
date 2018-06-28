#ifndef ROBOT_H
#define ROBOT_H

#include "world/world.h"
#include "trajectory/trajectory.h"
#include "misc/pose.h"
#include <cmath>

class Robot {
	private:
		// References to external information
		const World & world;
		const Trajectory & trajectory;

		// Timestep
		const double timestep = 0.1;

		// Position/Time state
		double t;
		Pose last_pose;
		Pose current_pose;

		// Robot properties
		const double requested_fov = 180.0f * M_PI / 180.0f;
		const double angle_step = 0.5f * M_PI / 180.0f;
		const double laser_range = 2.0f; // in meters

		// Odometry
		void odometry();

		// Laser sweep
		const int number_of_observations = static_cast<int>(requested_fov/angle_step) + 1;
		const double actual_fov = (number_of_observations - 1) * angle_step;
		void laser_sweep();
	public:
		Robot(const World & world_val, const Trajectory & trajectory_val);

		void simulate();
		void step();

};

#endif
