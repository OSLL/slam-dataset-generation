#include "trajectory/HermitePath.h"
#include <iostream>
#include <cmath>

#include <cassert>

using std::vector;
using std::cout;
using std::endl;

HermitePath::HermitePath(const vector<Pose> & intermediate_poses, const double & start_t_val)
	: start_pose({0.0f, 0.0f}, 0.0f)
	, end_pose({0.0f, 0.0f}, 0.0f)
{
	populateFromIntermediatePoses(intermediate_poses, start_t_val);
}

Pose HermitePath::operator()(double t) const {

	if (t < start_t)
		return start_pose;
	else if (t >= end_t)
		return end_pose;
	
	double t_integer_part;
	t = modf(t, &t_integer_part);

	const HermiteEdge & correct_edge = edges[static_cast<int>(t_integer_part)];
	
	Vec position = correct_edge(t);
	Vec derivative = correct_edge(t);

	return {position, derivative.radians()};
}

void HermitePath::populateFromIntermediatePoses(const vector<Pose> & intermediate_poses, const double & start_t_val) {
	
	// Cannot create a path with only one pose
	assert(intermediate_poses.size() > 1);

	// Initialize start and end times of the path
	start_t = start_t_val;
	end_t = start_t + static_cast<double>(start_t_val);

	// Create edges vector
	edges.clear();
	for (auto itr = intermediate_poses.begin() + 1; itr != intermediate_poses.end(); ++itr) {
		const Pose & pose1 = *(itr - 1);
		const Pose & pose2 = *itr;

		edges.push_back(HermiteEdge(pose1, pose2));
	}

	// Populate start_pose
	Vec start_position = edges.front()(0.0f);
	Vec start_velocity = edges.front().derivative(0.0f);
	start_pose = {start_position, start_velocity.radians()};

	// Populate end_pose
	Vec end_position = edges.back()(1.0f);
	Vec end_velocity = edges.back().derivative(1.0f);
	end_pose = {end_position, end_velocity.radians()};
}
