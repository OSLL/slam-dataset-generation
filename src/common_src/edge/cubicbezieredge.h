#ifndef CUBICBEZIEREDGE_H
#define CUBICBEZIEREDGE_H

#include "edge/edge.h"
#include <iostream>
#include <set>

class CubicBezierEdge : public Edge {
	public:
		CubicBezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point);

		// Store control points
		const Vec control_1;
		const Vec control_2;

		// Store vector coefficients for At^3 + Bt^2 + Ct + D
		const Vec A;
		const Vec B;
		const Vec C;
		const Vec & D; // Identical to end point, so no need to copy

		std::set<Vec> linear_intersection_points(const ObservationPath & op);
		Vec get_pos(const double & t);

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
