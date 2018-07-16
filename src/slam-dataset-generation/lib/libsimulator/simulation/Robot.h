#ifndef SIMULATION_ROBOT_H
#define SIMULATION_ROBOT_H

#include "world/World.h"
#include "trajectory/Trajectory.h"
#include "math/Pose.h"
#include <cmath>

#include <rosbag/bag.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/tfMessage.h>

class Robot {
	private:
		// References to external information
		const World & world;
		const Trajectory & trajectory;

		// Bag file
		rosbag::Bag bag;

		// Robot time & location
		double t;
		ros::Time ros_time;
		const double time_step = 0.01;
		Pose last_pose;
		Pose current_pose;

		// Laser sweep properties
		const double angle_step = 0.5f * M_PI / 180.0f;
		const double requested_fov = 180.0f * M_PI / 180.0f;
		const double laser_range = 2.0f; // in meters
		const int number_of_observations = static_cast<int>(requested_fov/angle_step) + 1;
		const double actual_fov = (number_of_observations - 1) * angle_step;

		geometry_msgs::TransformStamped generate_stamped_transform(const char * frame_id, const char * child_frame_id, const Pose & p);

		// Measurements
		void laser_sweep();
		void odometry();

		void step();
	public:
		Robot(const World & world_val, const Trajectory & trajectory_val);

		void simulate(const char * filename);
};

#endif
