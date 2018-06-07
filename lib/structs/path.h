#ifndef PATH_H
#define PATH_H

#include <vector>
#include "structs/edge.h"

class Path {
	private:
	public:
		Path(bool is_world_boundary_value = false);
		std::vector<Edge> edges;
		void add_edge(Edge e);
		bool is_world_boundary;
};

#endif
