#ifndef BEZIEREDGE_H
#define BEZIEREDGE_H

#include "world/edge.h"
#include <iostream>

class BezierEdge : public Edge {
	public:
		const Vec control_1;
		const Vec control_2;

		BezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point);

		double distance(const Vec & pos, const Vec & visual_range);

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
