#include "simulation/robot.h"
#include "observationpath/linesegment.h"
#include <iostream>

#include <rosgraph_msgs/Clock.h>
#include <std_msgs/Time.h>

using sensor_msgs::LaserScan;
using tf::tfMessage;
//using rosbag::bagmode::Write;

using std::cout;
using std::endl;

Robot::Robot(const World & world_val, const Trajectory & trajectory_val) :
	world(world_val),
	trajectory(trajectory_val),
	t(trajectory.t_min()),
	current_pose(trajectory.begin()),
	rate(1.0 / time_step),
	last_pose(current_pose)
{ }

Robot::~Robot() { }

void Robot::publish_clock() {
	std_msgs::Time time;
	time.data = ros::Time(t);

	static ros::Publisher clock_publisher = node_handle.advertise<std_msgs::Time>("clock", 1000);

	clock_publisher.publish(time);
}

tfMessage Robot::odometry() {
	// Use the transition between last_pose to current_pose to generate odometry data
	tfMessage odometry_msg;

	static uint32_t id = 0;
	odometry_msg.header.seq = id;
	id++

	odometry_msg.header.stamp = ros::Time::now();

	odometry_msg.header.frame_id = "1";



	return odometry_msg;
}

LaserScan Robot::laser_sweep() {
	
	// Sweep in clockwise direction
	const double angle_min = current_pose.theta + actual_fov/2.0f;
	const double angle_max = current_pose.theta - actual_fov/2.0f;

	// Initialize message
	sensor_msgs::LaserScan laser_scan_msg;

	for (int i = 0; i < number_of_observations; i++) {

		// Construct line segment that represents the lasers visual range
		double sweeping_angle = angle_min - i*angle_step;
		LineSegment view {
			{current_pose.pos},
			current_pose.pos + laser_range*Vec{cos(sweeping_angle), sin(sweeping_angle)}
		};

		// Take measurement
		float measurement = static_cast<float>(world.distance(view));
		laser_scan_msg.ranges.push_back((measurement == -1.0f)? laser_range + 1 : measurement);
	}

	static uint32_t id = 0;
	laser_scan_msg.header.seq = id;
	id++;

	laser_scan_msg.header.stamp = ros::Time::now();

	laser_scan_msg.header.frame_id = "1";

	laser_scan_msg.angle_min = static_cast<float>(angle_min);
	laser_scan_msg.angle_max = static_cast<float>(angle_max);
	laser_scan_msg.angle_increment = static_cast<float>(angle_step);

	laser_scan_msg.time_increment = static_cast<float>(0.0f);
	laser_scan_msg.time_increment = static_cast<float>(time_step);

	laser_scan_msg.range_min = static_cast<float>(0.0f);
	laser_scan_msg.range_max = static_cast<float>(laser_range);

	return laser_scan_msg;
}

void Robot::simulate() {
	while (t <= trajectory.t_max()) {
		step();
		rate.sleep();
	}
}

void Robot::step() {

	// Publish time
	publish_clock();
	
	// The reason we update state at the beginning of the step is because
	// odometry measurements assumes the last pose is known
	t += time_step;
	last_pose = current_pose;
	current_pose = trajectory(t);

	static ros::Publisher laser_scan_publisher = node_handle.advertise<sensor_msgs::LaserScan>("base_scan", 1000);
	//static ros::Publisher odometry_publisher = node_handle.advertise<tf::tfMessage>("tf", 1000);

	laser_scan_publisher.publish(laser_sweep());
	//bag.write("tf", ros::Time::now(), odometry());
}
