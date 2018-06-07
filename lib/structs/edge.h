#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "structs/vec2d.h"

class Edge {
	public:
		Edge(Vec2D v1_val = {0.0, 0.0}, Vec2D v2_val = {0.0, 0.0});
		Vec2D v1;
		Vec2D v2;
};

std::ostream & operator<<(std::ostream & o, Edge e);

#endif
