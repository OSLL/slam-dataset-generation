#include "pathfinding/find_trajectory.h"

#include "misc/vec.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

vector<Vec> intermediate_points {
	{1.29215882, 1.27719232},
	{2.19018437, 1.19736775},
	{3.21792473, 1.18738978},
	{3.96129038, 1.39193991},
	{4.20575294, 2.17022887},
	{4.24067596, 2.99840793},
	{3.87647668, 3.67691609},
	{3.00838547, 3.87647738},
	{2.10038181, 3.95131283},
	{1.34204913, 3.68190522},
	{1.07763052, 3.20794719},
	{0.89802539, 2.54440614},
	{0.95290474, 1.92576631}
};

Trajectory find_trajectory(const World & world, const critical_poses_t & critical_poses) {

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

	Trajectory trajectory(intermediate_poses);
	return trajectory;
}
