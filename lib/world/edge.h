#ifndef EDGE_H
#define EDGE_H

#include "misc/vec.h"

class Edge {
	public:
		virtual double distance(const Vec & pos, const Vec & visual_range) = 0;
};

#endif
