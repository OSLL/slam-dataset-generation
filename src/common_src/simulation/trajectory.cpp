#include "simulation/trajectory.h"
#include <vector>
#include <cmath>

using std::vector;

Trajectory::Trajectory(vector<Vec> line_path) :
	SplinePath(line_path)
{
	// Modify the SplinePath so that velocity is constant
}
