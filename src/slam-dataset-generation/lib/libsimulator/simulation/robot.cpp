#include "simulation/robot.h"
#include "observationpath/linesegment.h"
#include <iostream>

#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <tf/tfMessage.h>

using std::cout;
using std::endl;

Robot::Robot(const World & world_val, const Trajectory & trajectory_val) :
	world(world_val),
	trajectory(trajectory_val),

	t(trajectory.t_min()),
	ros_time((t == 0)? ros::TIME_MIN : ros::Time(t)),

	current_pose(trajectory.begin()),
	last_pose({0, 0}, 0)
{ }

void Robot::simulate(const char * filename) {

	try {
		bag.open(filename, rosbag::bagmode::Write);
	} catch (const std::exception e) {
		cout << "ERROR: Could not write to " << filename << "...  Returning..." << endl;
		return;
	}

	while (t <= trajectory.t_max()) {
		step();
	}
}

void Robot::step() {

	// The reason we update state at the beginning of the step is because
	// odometry measurements assumes the last pose is known

	laser_sweep();
	odometry();

	last_pose = current_pose;

	t += time_step;
	current_pose = trajectory(t);

	ros_time += ros::Duration().fromSec(time_step);
}

void Robot::laser_sweep() {
	
	// Initialize message
	sensor_msgs::LaserScan laser_scan_msg;

	laser_scan_msg.header.stamp = ros_time;
	laser_scan_msg.header.frame_id = "base_laser_link";

	// We scan in counterclockwise fashion
	laser_scan_msg.angle_min = -actual_fov / 2.0f;
	laser_scan_msg.angle_max =  actual_fov / 2.0f;

	laser_scan_msg.angle_increment = angle_step;

	laser_scan_msg.range_min = 0.0f;
	laser_scan_msg.range_max = laser_range;

	laser_scan_msg.ranges.reserve(number_of_observations);

	const double angle_min = current_pose.theta + laser_scan_msg.angle_min;

	for (int i = 0; i < number_of_observations; i++) {

		// Construct line segment that represents the lasers visual range
		double sweeping_angle = angle_min + i*angle_step;
		LineSegment view {
			{current_pose.pos},
			current_pose.pos + laser_range*Vec{cos(sweeping_angle), sin(sweeping_angle)}
		};

		// Take measurement
		float measurement = world.distance(view);
		laser_scan_msg.ranges.push_back((measurement == -1.0f)? laser_range + 1 : measurement);
	}

	bag.write("/base_scan", ros_time, laser_scan_msg);

	tf::tfMessage tf_message;
	tf_message.transforms.push_back(generate_stamped_transform("base_link", "base_laser_link", {{0.0f, 0.0f}, 0.0f}));
	bag.write("/tf", ros_time, tf_message);
}

void Robot::odometry() {
	
	tf::tfMessage tf_message;

	tf_message.transforms.push_back(generate_stamped_transform("base_footprint", "base_link", {{0.0f, 0.0f}, 0.0f}));
	tf_message.transforms.push_back(generate_stamped_transform("odom_combined", "base_footprint", current_pose));

	bag.write("/tf", ros_time, tf_message);
}

geometry_msgs::TransformStamped Robot::generate_stamped_transform(const char * frame_id, const char * child_frame_id, const Pose & change_in_pose) {

	geometry_msgs::TransformStamped ts;

	ts.header.stamp = ros_time;

	ts.header.frame_id = frame_id;
	ts.child_frame_id = child_frame_id;

	ts.transform.translation.x = change_in_pose.pos.x;
	ts.transform.translation.y = change_in_pose.pos.y;
	ts.transform.translation.z = 0.0f;

	ts.transform.rotation = tf::createQuaternionMsgFromYaw(change_in_pose.theta);

	return ts;
}
