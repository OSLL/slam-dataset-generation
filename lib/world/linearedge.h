#ifndef LINEAREDGE_H
#define LINEAREDGE_H

#include "world/edge.h"
#include <iostream>
#include <set>

class LinearEdge : public Edge {
	public:
		LinearEdge(const Vec & start_point, const Vec & end_point);

		std::set<Vec> intersection(const Vec & pos, const Vec & visual_range);

		void print(std::ostream & o = std::cout, int tabs = 0) const;
};

#endif
