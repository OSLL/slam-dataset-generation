#ifndef LINEAREDGE_H
#define LINEAREDGE_H

#include "edge/observable/ObstacleEdge.h"
#include "observationpath/ObservationPath.h"
#include <iostream>
#include <set>

class LinearEdge : public ObstacleEdge {
	public:
		LinearEdge(const Vec & start_point, const Vec & end_point);
	
		const Vec direction;

		std::set<Vec> linear_intersection_points(const ObservationPath & op) const;
		Vec get_pos(const double & t) const;

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
