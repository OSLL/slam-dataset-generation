#ifndef ROBOT_H
#define ROBOT_H

#include "world/world.h"
#include "trajectory/trajectory.h"
#include "misc/pose.h"
#include <cmath>

#include <ros/ros.h>
//#include <rosbag/bag.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/tfMessage.h>

class Robot {
	private:
		// References to external information
		const World & world;
		const Trajectory & trajectory;

		// Timestep
		const double time_step = 0.1;
		ros::Rate rate;

		// Position/Time state
		double t;
		Pose last_pose;
		Pose current_pose;

		// Bag file
		//rosbag::Bag bag;

		ros::NodeHandle node_handle;

		// Robot properties
		const double requested_fov = 180.0f * M_PI / 180.0f;
		const double angle_step = 0.5f * M_PI / 180.0f;
		const double laser_range = 2.0f; // in meters

		// Timekeeping
		void publish_clock();

		// Odometry
		tf::tfMessage odometry();

		// Laser sweep
		const int number_of_observations = static_cast<int>(requested_fov/angle_step) + 1;
		const double actual_fov = (number_of_observations - 1) * angle_step;
		sensor_msgs::LaserScan laser_sweep();
	public:
		Robot(const World & world_val, const Trajectory & trajectory_val);
		~Robot();

		void simulate();
		void step();

};

#endif
