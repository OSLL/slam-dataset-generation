#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include "structs/vec.h"
#include "structs/splinepath.h"

class Trajectory : public SplinePath {
	public:
		Trajectory(std::vector<Vec> line_path);
};

#endif
