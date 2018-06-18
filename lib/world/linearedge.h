#ifndef LINEAREDGE_H
#define LINEAREDGE_H

#include "world/edge.h"
#include "misc/observationpath.h"
#include <iostream>
#include <set>

class LinearEdge : public Edge {
	public:
		LinearEdge(const Vec & start_point, const Vec & end_point);

		std::set<Vec> linear_intersection_points(const ObservationPath & op);

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
