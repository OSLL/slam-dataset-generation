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
	intermediate_points.reserve(linear_trajectory->edges.size() + 1);

	intermediate_points.push_back(linear_trajectory->getStart());
	for (const auto & edge : linear_trajectory->edges) {
		intermediate_points.push_back(edge->getEnd());
	}

	vector<Pose> intermediate_poses;
	for (vector<Vec>::iterator itr = intermediate_points.begin(); itr != intermediate_points.end(); itr++) {

		const Vec & pos = *itr;

		double theta;

		if (itr == intermediate_points.end() - 1) {
			// Last element.  Use preveious two
			theta = (*itr - *(itr - 1)).radians();
		} else {
			// Not last element. Use next two
			theta = (*(itr + 1) - *itr).radians();
		}

		intermediate_poses.push_back({pos, theta});
	}


	for (const Pose & pose : intermediate_poses) {
		//cout << pose << endl;
	}

	Trajectory trajectory(intermediate_poses);
	return trajectory;
}
