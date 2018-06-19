#ifndef LINEAREDGE_H
#define LINEAREDGE_H

#include "world/edge.h"
#include "misc/observationpath.h"
#include <iostream>
#include <set>

class LinearEdge : public Edge {
	public:
		LinearEdge(const Vec & start_point, const Vec & end_point);
	
		const Vec direction;

		std::set<Vec> linear_intersection_points(const ObservationPath & op);
		Vec get_pos(const double & t);

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
