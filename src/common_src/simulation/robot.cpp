#include "simulation/robot.h"
#include "observationpath/linesegment.h"
#include <iostream>

using std::cout;
using std::endl;

Robot::Robot(const World & world_val, const Trajectory & trajectory_val) :
	world(world_val),
	trajectory(trajectory_val),
	t(trajectory.t_min()),
	current_pose(trajectory.begin()),
	last_pose(current_pose)
{ }

void Robot::odometry() {
	// Use the transition between last_pose to current_pose to generate odometry data
}

void Robot::laser_sweep() {
	
	// Sweep in clockwise direction
	const double angle_min = current_pose.theta + actual_fov/2.0f;
	const double angle_max = current_pose.theta - actual_fov/2.0f;

	// Store measurements
	double * measurements = new double[number_of_observations];

	for (int i = 0; i < number_of_observations; i++) {

		// Construct line segment that represents the lasers visual range
		double sweeping_angle = angle_min - i*angle_step;
		LineSegment view {
			{current_pose.pos},
			current_pose.pos + laser_range*Vec{cos(sweeping_angle), sin(sweeping_angle)}
		};

		// Take measurement
		measurements[i] = world.distance(view);
	}

	// Commit measurements to bag file
	

	// Free allocated memory
	delete[] measurements;
}

void Robot::simulate() {
	while (t <= trajectory.t_max()) {
		step();
	}
}

void Robot::step() {
	
	// The reason we update state at the beginning of the step is because
	// odometry measurements assumes the last pose is known
	t += timestep;
	last_pose = current_pose;
	current_pose = trajectory(t);

	odometry();
	laser_sweep();
}
