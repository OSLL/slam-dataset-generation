#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include "misc/vec.h"
#include "simulation/splinepath.h"

class Trajectory : public SplinePath {
	public:
		Trajectory(std::vector<Vec> line_path);
};

#endif
