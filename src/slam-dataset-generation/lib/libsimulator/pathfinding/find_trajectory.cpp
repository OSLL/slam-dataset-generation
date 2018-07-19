#include "pathfinding/find_trajectory.h"

#include "math/Vec.h"
#include <vector>
#include <iostream>

#include "obstacle/Obstacle.h"
#include <memory>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

using std::unique_ptr;

Trajectory find_trajectory(World & world, const vector<Pose> & critical_poses) {

	unique_ptr<Obstacle> linear_trajectory = world.extractLinearTrajectory();

	vector<Vec> intermediate_points;

	intermediate_points.push_back(linear_trajectory->getStart());
	for (const auto & edge : linear_trajectory->getEdges()) {
		intermediate_points.push_back(edge->getEnd());
	}

	vector<Pose> intermediate_poses;
	double theta;
	for (int i = 0; i < intermediate_points.size() - 1; ++i) {

		const Vec & p1 = intermediate_points[i];
		const Vec & p2 = intermediate_points[i + 1];

		theta = (p2 - p1).radians();
		
		intermediate_poses.push_back({p1, theta});
	}
	intermediate_poses.push_back({intermediate_points.back(), theta});

	/*
	for (const Pose & pose : intermediate_poses) {
		cout << pose << endl;
	}
	*/

	Trajectory trajectory(intermediate_poses);
	return trajectory;
}
