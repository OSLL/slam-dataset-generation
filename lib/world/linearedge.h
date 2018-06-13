#ifndef LINEAREDGE_H
#define LINEAREDGE_H

#include "world/edge.h"

class LinearEdge : public Edge {
	public:
		// Start point is determined by prior edge or move-to command so we
		// can use reference.  The next edge will use our end as their start
		const Vec & start;
		const Vec end;
		LinearEdge(const Vec & start_point, const Vec & end_point);
		double distance(const Vec & pos, const Vec & visual_range);
};

#endif
