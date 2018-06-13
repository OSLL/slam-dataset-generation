#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "world/path.h"
#include "misc/vec.h"

class Graph {
	public:
		Graph();
		void add_edge(Path p);
};

#endif
