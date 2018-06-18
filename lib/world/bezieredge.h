#ifndef BEZIEREDGE_H
#define BEZIEREDGE_H

#include "world/edge.h"
#include <iostream>
#include <set>

class BezierEdge : public Edge {
	public:
		const Vec control_1;
		const Vec control_2;

		BezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point);

		std::set<Vec> linear_intersection_points(const ObservationPath & op);

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
