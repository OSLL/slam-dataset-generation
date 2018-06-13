#ifndef BEZIEREDGE_H
#define BEZIEREDGE_H

#include "world/edge.h"

class BezierEdge : public Edge {
	public:
		// Start point is determined by prior edge or move-to command so we
		// can use reference.  The next edge will use our end as their start
		const Vec & start;
		const Vec control_1;
		const Vec control_2;
		const Vec end;

		BezierEdge(const Vec & start_point, const Vec & c1, const Vec & c2, const Vec & end_point);
		double distance(const Vec & pos, const Vec & visual_range);
};

#endif
