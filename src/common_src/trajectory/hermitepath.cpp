#include "trajectory/hermitepath.h"
#include <iostream>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;

HermitePath::HermitePath(const vector<Pose> & intermediate_poses) {
	if (intermediate_poses.size() < 2) {
		cout << "Requested spline interpolation of a list of one or fewer points." << endl;
		return;
	}

	for (int i = 0; i < intermediate_poses.size() - 1; i++) {
		edges.push_back(HermiteEdge{intermediate_poses[i], intermediate_poses[i+1]});
	}
}

Pose HermitePath::operator()(double t) {

	int edge_index;

	if (t < 0) {
		edge_index = 0;
		t = 0;
	} else if (t > edges.size()) {
		edge_index = edges.size() - 1;
		t = 0;
	} else {
		double temp;
		t = modf(t, &temp);
		edge_index = static_cast<int>(temp);
	}

	Vec pos = edges[edge_index](t);
	Vec derivative = edges[edge_index].derivative(t);

	return {pos, derivative.radians()};
}
