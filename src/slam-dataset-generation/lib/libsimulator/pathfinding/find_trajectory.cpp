#include "pathfinding/find_trajectory.h"

#include "math/Vec.h"
#include <vector>
#include <iostream>

#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

Trajectory find_trajectory(World & world, const vector<Pose> & critical_poses) {

	Obstacle * linear_trajectory = nullptr;

	for (auto itr = world.all_obstacles.begin(); itr != world.all_obstacles.end(); itr++) {

		if ((*itr)->id == "linear_trajectory") {
			linear_trajectory = *itr;
			world.all_obstacles.erase(itr);
			break;
		}
	}

	if (linear_trajectory == nullptr) {
		cout << "Could not locate path with id=\"linear_trajectory\"" << endl;
		exit(-1);
	} else {
		// Remove linear_trajectory from world.interior_obstacles
		vector<Obstacle *>::iterator pos = std::find(world.interior_obstacles.begin(), world.interior_obstacles.end(), linear_trajectory);
		world.interior_obstacles.erase(pos);
	}

	

	vector<Vec> intermediate_points;
	intermediate_points.reserve(linear_trajectory->edges.size() + 1);

	intermediate_points.push_back(linear_trajectory->start);
	for (ObstacleEdge * e : linear_trajectory->edges) {
		intermediate_points.push_back(e->end);
	}

	delete linear_trajectory;

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
