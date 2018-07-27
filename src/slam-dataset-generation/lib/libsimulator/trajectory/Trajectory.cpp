#include "trajectory/Trajectory.h"
#include <vector>
#include <cmath>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::ostream;

Trajectory::Trajectory(vector<Pose> intermediate_poses) :
	HermitePath(intermediate_poses)
{ }

void Trajectory::print(ostream & o, int tabs) const {
	
	for (int i = 0; i < tabs; i++)
		o << '\t';
	
	o << "Trajectory:" << endl;
	for (auto && edge : edges)
	{
		edge.print(o, tabs + 1);
		cout << endl;
	}
}
