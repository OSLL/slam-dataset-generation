#include "trajectory/Trajectory.h"
#include <vector>
#include <cmath>

using std::vector;

#include <iostream>
using std::cout;
using std::endl;

Trajectory::Trajectory(vector<Pose> intermediate_poses) :
	HermitePath(intermediate_poses)
{
	for (auto itr = edges.begin() + 1; itr != edges.end(); ++itr) {
		Vec p1 = (*(itr - 1)).derivative(1.0f);
		Vec p2 = (*itr).derivative(0.0f);

		cout << p1 << " -> " << p2 << endl;
	}
}

Pose Trajectory::begin() const {
	return (*this)(0);
}

Pose Trajectory::end() const {
	return (*this)(edges.size() + 1);
}
