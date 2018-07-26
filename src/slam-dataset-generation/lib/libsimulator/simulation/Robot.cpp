#include "simulation/Robot.h"
#include "observationpath/LineSegment.h"
#include <iostream>
#include <cstdlib>

#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <tf/tfMessage.h>

using std::abs;
using std::cout;
using std::endl;
using std::setprecision;
using std::fixed;
using std::flush;

Robot::Robot(const World & world_val, const Trajectory & trajectory_val) :
	world(world_val),
	trajectory(trajectory_val),

	t(trajectory.getStartTime()),
	ros_time((t == 0)? ros::TIME_MIN : ros::Time(t)),

	current_pose(trajectory.getStartPose()),
	last_pose(trajectory.getStartPose())
{ }

void Robot::simulate(const char * filename) {

	try {
		bag.open(filename, rosbag::bagmode::Write);
	} catch (const std::exception e) {
		cout << "ERROR: Could not write to " << filename << "...  Returning..." << endl;
		return;
	}

	cout << setprecision(2) << fixed;

	while (t <= trajectory.getEndTime()) {
		cout << "\r" << t << "/" << trajectory.getEndTime() << std::flush;
		step();
	}
	cout << endl;
}

void Robot::step() {

	t += time_step;
	ros_time += ros::Duration().fromSec(time_step);

	last_pose = current_pose;
	current_pose = trajectory(t);

	laser_sweep();
	odometry();
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
		float measurement = world.distance(t, view);
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

	// Perform optional discontinuous motion detection

	double theta_delta = abs(last_pose.theta - current_pose.theta);
	if (theta_delta > M_PI)
		theta_delta = 2*M_PI - theta_delta;

	const double theta_discontinuity_threshold = 0.1;
	bool theta_discontinuity = theta_delta > theta_discontinuity_threshold;

	Vec position_delta = last_pose.pos - current_pose.pos;
	position_delta.x = abs(position_delta.x);
	position_delta.y = abs(position_delta.y);

	const double position_coordinate_discontinuity_threshold = 0.1;
	bool position_discontinuity = (position_delta.x > position_coordinate_discontinuity_threshold) ||
				      (position_delta.y > position_coordinate_discontinuity_threshold);


	if (theta_discontinuity || position_discontinuity)
	{
		cout << "Discontinuity in trajectory detected:" << endl;
		cout << "\t" << last_pose << endl;
		cout << "\t" << current_pose << endl;
	}
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
